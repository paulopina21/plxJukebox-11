

#ifdef HAS_GLES

#include "GUIShader.h"
#include "../../guilib/MatrixGLES.h"
#include "utils/log.h"

CGUIShader::CGUIShader( const std::string& vert, const std::string& frag ) : CGLSLShaderProgram(vert, frag)
{
  // Initialise values
  m_hTex0   = 0;
  m_hTex1   = 0;
  m_hProj   = 0;
  m_hModel  = 0;
  m_hPos    = 0;
  m_hCol    = 0;
  m_hCord0  = 0;
  m_hCord1  = 0;

  m_proj   = NULL;
  m_model  = NULL;
}

void CGUIShader::OnCompiledAndLinked()
{
  // This is called after CompileAndLink()

  // Variables passed directly to the Fragment shader
  m_hTex0   = glGetUniformLocation(ProgramHandle(), "m_samp0");
  m_hTex1   = glGetUniformLocation(ProgramHandle(), "m_samp1");
  // Variables passed directly to the Vertex shader
  m_hProj   = glGetUniformLocation(ProgramHandle(), "m_proj");
  m_hModel  = glGetUniformLocation(ProgramHandle(), "m_model");
  m_hPos    = glGetAttribLocation(ProgramHandle(),  "m_attrpos");
  m_hCol    = glGetAttribLocation(ProgramHandle(),  "m_attrcol");
  m_hCord0  = glGetAttribLocation(ProgramHandle(),  "m_attrcord0");
  m_hCord1  = glGetAttribLocation(ProgramHandle(),  "m_attrcord1");

  // It's okay to do this only one time. Textures units never change.
  glUseProgram( ProgramHandle() );
  glUniform1i(m_hTex0, 0);
  glUniform1i(m_hTex1, 1);
  glUseProgram( 0 );
}

bool CGUIShader::OnEnabled()
{
  // This is called after glUseProgram()

  glUniformMatrix4fv(m_hProj,  1, GL_FALSE, g_matrices.GetMatrix(MM_PROJECTION));
  glUniformMatrix4fv(m_hModel, 1, GL_FALSE, g_matrices.GetMatrix(MM_MODELVIEW));

  return true;
}

void CGUIShader::Free()
{
  // Do Cleanup here
  CGLSLShaderProgram::Free();
}

#endif
