#ifndef FILE_HANDLE_H
#define FILE_HANDLE_H

namespace Filesystem
{class FileHandle;}
#include "FilesystemReader.h"
#include "FilesystemDefines.h"

/* @brief returned on file deletion as well as if it should be excluded */
#define Filesystem_FILE_ERROR   -1
#define Filesystem_FILE_OK       0
#define Filesystem_FILE_MODIFIED 1

#define Filesystem_IS_FOLDER     3
#define Filesystem_FOLDER_OK     4
#define Filesystem_FOLDER_EMPTY  5
#define Filesystem_FILE_IGNORED  6

#ifdef _WIN32
#define NEWLINE_CHAR '\n'
#elif __linux__
#define NEWLINE_CHAR '\n'
#else //__APPLE__ 
#define NEWLINE_CHAR '\r'
#endif

namespace Filesystem
{

class FileHandle
{
  public:
    FileHandle(std::string filename);
    ~FileHandle();

    /* open and close internal file handle */
    bool Open();
    void Close();
    bool IsOpen();
    
    /* read data */
    void ReadLine(std::string& out);
    FILE* GetFileStruct();

    /* move read pointer in direction */
    void MovePosition(s32 move);
    void EatWhitespace();

    /*!*****************************
      *  @brief Reads one of any type from file in byte form
      *
      *  @param out - The variable to fill with read data
    *******************************/
    template<typename T>
    void Read(T& out)
    {
      ReadBytes(&out, sizeof(T));
    }

    /*!*****************************
    *  @brief Reads one of any integral type
    *
    *  @param out - The variable to fill with read data
    *******************************/
    template<typename T>
    void ReadIntegral(T& out)
    {
      EatWhitespace();
      assertion(IsOpen());
      assertion(!Eof());

      String str;
      s32 lineLen = 0;
      c08 c = m_readPointer[lineLen++];
      while((c >= '0' && c <= '9') || (c == '-' && lineLen == 1))
      {
        str += c;
        c = m_readPointer[lineLen++];
      }
      --lineLen;

      out = atoi(str.c_str());
      m_readPointer += lineLen;
    }

    /*!*****************************
    *  @brief Reads one of any Float type
    *
    *  @param out - The variable to fill with read data
    *******************************/
    template<typename T>
    void ReadFloat(T& out)
    {
      EatWhitespace();
      assertion(IsOpen());
      assertion(!Eof());

      String str;
      bool hasDot = false;
      s32 lineLen = 0;
      c08 c = m_readPointer[lineLen++];
      while((c >= '0' && c <= '9') || (c == '-' && lineLen == 1) || (c == '.' && !hasDot))
      {
        if(c == '.')
          hasDot = true;
        str += c;
        c = m_readPointer[lineLen++];
      }
      --lineLen;

      out = atof(str.c_str());
      m_readPointer += lineLen;
    }

    /*!*****************************
      *  @brief Reads an array of any type from file
      *
      *  @param out - The array to fill, must be continuous memory
      *  @param arraySize - The number of elements in the array
    *******************************/
    template<typename T>
    void ReadArray(T* out, u32 arraySize)
    {
      ReadBytes(out, sizeof(T) * arraySize);
    }

    /*!*****************************
      *  @brief Reads specified number of bytes from file
      *
      *  @param out - The variable to fill with read data
      *  @param numBytes - The number of bytes to be read
    *******************************/
    template<typename T>
    void ReadBytes(T* out, u32 numBytes)
    {
      assertion(m_readPointer + numBytes <= m_file + m_size);
      if(!IsOpen())
        Open();
      memcpy((c08*)(out), m_readPointer, numBytes);
      m_readPointer += numBytes;
    }

    bool Eof();

    /* Get File information */
    const std::string&  GetFileName() const;
    std::string&        GetFileExtension();
    u32                 GetFileSize() const;
    s64                 GetLastModified() const;

    const char* ReadFile();

    //returns Filesystem_FILE_OK, Filesystem_FILE_ERROR, Filesystem_FILE_MODIFIED defined in precompiled
    s32 GetFileState(void);
    
    /* Update file state */
    s32 CheckFile(void);

  private:
    std::string m_fileName;
    std::string m_extension;

    u32  m_size;
    s64  m_timeModified;

    char* m_file;
    char* m_readPointer;

    s32 m_fileState;
};

typedef std::list<FileHandle*> FileCont;
typedef FileCont::iterator     FileContIt;

}//Filesystem
#endif
