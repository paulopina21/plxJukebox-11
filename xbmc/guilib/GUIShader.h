

#ifndef GUI_SHADER_H
#define GUI_SHADER_H

#pragma once

#include "Shader.h"

using namespace Shaders;

class CGUIShader : public CGLSLShaderProgram
{
public:
  CGUIShader( const char *shader = 0 );
  void OnCompiledAndLinked();
  bool OnEnabled();
  void Free();

  GLint GetPosLoc()   { return m_hPos;   }
  GLint GetColLoc()   { return m_hCol;   }
  GLint GetCord0Loc() { return m_hCord0; }
  GLint GetCord1Loc() { return m_hCord1; }
  
protected:
  GLint m_hTex0;
  GLint m_hTex1;
  GLint m_hProj;
  GLint m_hModel;
  GLint m_hPos;
  GLint m_hCol;
  GLint m_hCord0;
  GLint m_hCord1;

  GLfloat *m_proj;
  GLfloat *m_model;
};

#endif // GUI_SHADER_H
