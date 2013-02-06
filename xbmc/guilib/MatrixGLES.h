

#ifndef MATRIX_GLES_H
#define MATRIX_GLES_H

#pragma once

#include <vector>

using namespace std;

enum EMATRIXMODE
{
  MM_PROJECTION = 0,
  MM_MODELVIEW,
  MM_TEXTURE,
  MM_MATRIXSIZE  // Must be last! used for size of matrices
};

class CMatrixGLES
{
public:
  CMatrixGLES();
  ~CMatrixGLES();
  
  GLfloat* GetMatrix(EMATRIXMODE mode);

  void MatrixMode(EMATRIXMODE mode);
  void PushMatrix();
  void PopMatrix();
  void LoadIdentity();
  void Ortho(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
  void Ortho2D(GLfloat l, GLfloat r, GLfloat b, GLfloat t);
  void Frustum(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
  void Translatef(GLfloat x, GLfloat y, GLfloat z);
  void Scalef(GLfloat x, GLfloat y, GLfloat z);
  void Rotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
  void MultMatrixf(const GLfloat *matrix);
  void LookAt(GLfloat eyex, GLfloat eyey, GLfloat eyez, GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat upx, GLfloat upy, GLfloat upz);
  void PrintMatrix(void);
  bool Project(GLfloat objx, GLfloat objy, GLfloat objz, const GLfloat modelMatrix[16], const GLfloat projMatrix[16], const GLint viewport[4], GLfloat* winx, GLfloat* winy, GLfloat* winz);

protected:
  vector<GLfloat*> m_matrices[(int)MM_MATRIXSIZE];
  GLfloat *m_pMatrix;
  EMATRIXMODE m_matrixMode;
};

extern CMatrixGLES g_matrices;

#endif // MATRIX_GLES_H
