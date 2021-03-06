#ifndef GLFONT_MODULE
#define GLFONT_MODULE
#include <gl\gl.h>
class GLFont
{
 public:
  GLFont();
  ~GLFont();
  void SetTexture(GLuint Tex, int xCount, int yCount);
  void SetFontProperties(int Width, int Height, int Spacing);
  void SetDisplayMode(int dWidth, int dHeight);
  void SetBase(int Base);
  GLvoid KillFont(GLvoid);
  GLvoid BuildFont(int size);
  GLvoid Print(GLint x, GLint y, char *string);
 private:
  GLuint fTexture[1];
  GLuint fBase;
  int    fWidth;
  int    fHeight;
  int    fSpacing; 
  int    fStartPos;
  int    fxCount;
  int    fyCount;
  int    fdWidth;
  int    fdHeight;
};


#endif