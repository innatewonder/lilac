#pragma once

class Shader
{
public:
  Shader(std::string vs, std::string fs);
  ~Shader();
  void Bind(Math::Matrix& proj, Math::Matrix& view);
  void UnBind();
  s32  GetID();

  void AddFile(std::string filename, s32 type);
  void Link();

private:

  const char* ReadEntireFile(std::string filename);

  s32 m_id;
};

#if PLATFORM == PLAT_UNIX
#define CHECK_GL_ERR \
{ \
  int err = glGetError();\
  if (err) { \
    fprintf(stderr, "OpenGL error (at line %d in %s): %s\n", \
      __LINE__, __FILE__, gluErrorString(err)); \
    exit(-1); } \
}
#else
#define CHECK_GL_ERR \
{ \
int err = glGetError(); \
if(err) { \
    fprintf(stderr, "OpenGL error (at line %d in %s): %i\n", \
    __LINE__, __FILE__, err); \
    __debugbreak(); } \
}
#endif
