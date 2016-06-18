#include "CommonPrecompiled.h"
#include <fstream>
#include "Shader.h"

namespace Graphics
{
  Shader::Shader(std::string vs, std::string fs)
  {
    m_id = glCreateProgram();

    AddFile(vs, GL_VERTEX_SHADER);
    AddFile(fs, GL_FRAGMENT_SHADER);

    glBindAttribLocation(m_id, 0, "vertex");
    glBindAttribLocation(m_id, 1, "vertexNormal");
    glBindAttribLocation(m_id, 2, "vertexTexture");
    CHECK_GL_ERR;
  }

  Shader::~Shader()
  {
    glDeleteProgram(m_id);
    m_id = 0;
  }

  void Shader::Bind(Math::Matrix& proj, Math::Matrix& view)
  {
    glUseProgram(m_id);
    CHECK_GL_ERR;

    int loc = glGetUniformLocation(m_id, "ProjectionMatrix");
    CHECK_GL_ERR;
    glUniformMatrix4fv(loc, 1, GL_FALSE, proj.v);
    CHECK_GL_ERR;

    loc = glGetUniformLocation(m_id, "ViewMatrix");
    glUniformMatrix4fv(loc, 1, GL_FALSE, view.v);
    CHECK_GL_ERR;
  }

  void Shader::UnBind()
  {
    glUseProgram(0);
    CHECK_GL_ERR;
  }

  s32 Shader::GetID()
  {
    return m_id;
  }

  void Shader::AddFile(std::string filename, s32 type)
  {
    std::cout << "Adding " << filename << " to shader " << m_id << "... ";
    const char* fileData = ReadEntireFile(filename);

    s32 current = glCreateShader(type);
    glAttachShader(m_id, current);
    glShaderSource(current, 1, &fileData, NULL);
    glCompileShader(current);
    delete fileData;
    CHECK_GL_ERR;


    // Get the compilation status
    int status = 0;
    glGetShaderiv(current, GL_COMPILE_STATUS, &status);

    // If compilation status is not OK, get and print the log message.
    if(status != 1) {
      std::cout << "Failure" << std::endl;
      int length = 0;
      glGetShaderiv(current, GL_INFO_LOG_LENGTH, &length);
      char* buffer = new char[length];
      glGetShaderInfoLog(current, length, NULL, buffer);
      printf("Compile log for %s:\n%s\n", filename.c_str(), buffer);
      delete buffer;
    }
    else
    {
      std::cout << "Success" << std::endl;
    }
    CHECK_GL_ERR;
  }

  void Shader::Link()
  {
    std::cout << "Linking Shader " << m_id << "... ";
    glLinkProgram(m_id);
    int status;
    glGetProgramiv(m_id, GL_LINK_STATUS, &status);
    CHECK_GL_ERR;

    // If link failed, get and print log
    if(status != 1) {
      std::cout << "Failure" << std::endl;
      int length;
      glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &length);
      char* buffer = new char[length];
      glGetProgramInfoLog(m_id, length, NULL, buffer);
      printf("Link log:\n%s\n", buffer);
      delete buffer;
    }
    else
    {
      std::cout << "Success" << std::endl;
    }
    CHECK_GL_ERR;
  }

  const char *Shader::ReadEntireFile(std::string filename)
  {
    char* ret;
    std::ifstream file(filename.c_str(), std::ios_base::binary);

    if(file.is_open())
    {
      file.seekg(0, std::ios_base::end);
      s32 size = file.tellg();
      file.seekg(0, std::ios_base::beg);

      if(size > 0)
      {
        ret = new char[size + 1];
        file.read(ret, size);
        ret[size] = '\0';
      }
      file.close();
    }
    return ret;
  }
}
