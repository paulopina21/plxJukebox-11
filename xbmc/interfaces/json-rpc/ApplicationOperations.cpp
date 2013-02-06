

#include "ApplicationOperations.h"
#include "Application.h"
#include "ApplicationMessenger.h"
#include "FileItem.h"
#include "Util.h"
#include "utils/log.h"
#include "GUIInfoManager.h"
#include "system.h"

using namespace JSONRPC;

JSON_STATUS CApplicationOperations::GetProperties(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result)
{
  CVariant properties = CVariant(CVariant::VariantTypeObject);
  for (unsigned int index = 0; index < parameterObject["properties"].size(); index++)
  {
    CStdString propertyName = parameterObject["properties"][index].asString();
    CVariant property;
    JSON_STATUS ret;
    if ((ret = GetPropertyValue(propertyName, property)) != OK)
      return ret;

    properties[propertyName] = property;
  }

  result = properties;

  return OK;
}

JSON_STATUS CApplicationOperations::SetVolume(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result)
{
  int oldVolume = g_application.GetVolume();
  int volume = (int)parameterObject["volume"].asInteger();
  
  g_application.SetVolume(volume);

  g_application.getApplicationMessenger().ShowVolumeBar(oldVolume < volume);

  return GetPropertyValue("volume", result);
}

JSON_STATUS CApplicationOperations::SetMute(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result)
{
  if ((parameterObject["mute"].isString() && parameterObject["mute"].asString().compare("toggle") == 0) ||
      (parameterObject["mute"].isBoolean() && parameterObject["mute"].asBoolean() != g_application.IsMuted()))
    g_application.getApplicationMessenger().SendAction(CAction(ACTION_MUTE));
  else if (!parameterObject["mute"].isBoolean() && !parameterObject["mute"].isString())
    return InvalidParams;

  return GetPropertyValue("muted", result);
}

JSON_STATUS CApplicationOperations::Quit(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result)
{
  g_application.getApplicationMessenger().Quit();
  return ACK;
}

JSON_STATUS CApplicationOperations::GetPropertyValue(const CStdString &property, CVariant &result)
{
  if (property.Equals("volume"))
    result = g_application.GetVolume();
  else if (property.Equals("muted"))
    result = g_application.IsMuted();
  else if (property.Equals("name"))
    result = "XBMC";
  else if (property.Equals("version"))
  {
    result = CVariant(CVariant::VariantTypeObject);
    result["major"] = VERSION_MAJOR;
    result["minor"] = VERSION_MINOR;
#ifdef GIT_REV
    result["revision"] = GIT_REV;
#endif
    CStdString tag(VERSION_TAG);
    if (tag.ToLower().Equals("-pre"))
      result["tag"] = "alpha";
    else if (tag.ToLower().Left(5).Equals("-beta"))
      result["tag"] = "beta";
    else if (tag.ToLower().Left(3).Equals("-rc"))
      result["tag"] = "releasecandidate";
    else if (tag.empty())
      result["tag"] = "stable";
    else
      result["tag"] = "prealpha";
  }
  else
    return InvalidParams;

  return OK;
}
