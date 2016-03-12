#include "CommonPrecompiled.h"
#include "FileHandle.h"

#ifdef _WIN32
#pragma warning( disable: 4996 ) //fopen/read warning
#endif

namespace Filesystem
{

  /*!*****************************
   *  @brief Constructor for FileHandle using external file
   *
   *  @param filename - Name of the file to open
  *******************************/
  FileHandle::FileHandle(std::string filename) 
    : m_fileName(filename), m_timeModified(0), 
    m_fileState(Filesystem_FILE_ERROR), m_file(nullptr)
  {
    s32 pos = m_fileName.find_last_of('.');
    if((pos == std::string::npos)) // || (pos < fileName_.size() - 4))
    {
      m_fileState = Filesystem_IS_FOLDER;
      return;
    }
    else
    {
      ++pos;
      m_extension = m_fileName.substr(pos, std::string::npos);
    }

    CheckFile();
  }

  /*!*****************************
   *  @brief Destructor
  *******************************/
  FileHandle::~FileHandle()
  {
    Close();
  }

  /*!*****************************
   *  @brief Opens internal file handle
   *
   *  @return true if the file is now open
  *******************************/
  bool FileHandle::Open()
  {
    if(IsOpen())
    {
      m_readPointer = m_file;
      return true;
    }
    
    ReadFile();
    return IsOpen();
  }

  /*!*****************************
   *  @brief Closes internal file handle
  *******************************/
  void FileHandle::Close()
  {
    if(m_file)
    {
      delete[] m_file;
      m_file = nullptr;
      m_readPointer = nullptr;
    }
  }

  /*!*****************************
   *  @brief Closes internal file handle
  *******************************/
  bool FileHandle::IsOpen()
  {
    return m_file != nullptr;
  }

  /*!*****************************
   *  @brief Gets a file struct, USER IS RESPONSABLE FOR CLOSING
   *  
   *  @return The FILE* of the file
  *******************************/
  FILE* FileHandle::GetFileStruct()
  {
    //todo THIS NEEDS TESTING
    return fopen(m_fileName.c_str(), "r");
  }

  void FileHandle::MovePosition(s32 move)
  {
    assertion(IsOpen());
    assertion(m_readPointer + move >= m_file);
    assertion(m_readPointer + move <= m_file + m_size);

    m_readPointer += move;
  }

  void FileHandle::EatWhitespace()
  {
    assertion(IsOpen());
    while(!Eof() && 
        (*m_readPointer == ' '
      || *m_readPointer == '\t'
      || *m_readPointer == '\n'
      || *m_readPointer == '\r'))
    {
      ++m_readPointer;
    }
  }

  /*!*****************************
   *  @brief Read a line into out ( assumes text file )
   *
   *  @param out - The variable to be filled with data
  *******************************/
  void FileHandle::ReadLine(std::string& out)
  {
    assertion(IsOpen());
    assertion(!Eof());
    
    s32 lineLen = 0;
    c08 c;
    do
    {
      c = m_readPointer[lineLen++];
    } while(c != '\n');

    out.assign(m_readPointer, lineLen);
    m_readPointer += lineLen;
  }

  /*!*****************************
   *  @brief Checks if the pointer is at the end of the file
   *
   *  @return True if at end of file
  *******************************/
  bool FileHandle::Eof()
  {
    assertion(IsOpen());
    return m_readPointer >= m_file + m_size;
  }

  /*!*****************************
   *  @brief Gets the file name
   *
   *  @return The file name
  *******************************/
  const std::string& FileHandle::GetFileName() const
  {
    return m_fileName;
  }

  /*!*****************************
   *  @brief Gets the file state: either Filesystem_FILE_OK, Filesystem_FILE_ERROR, or Filesystem_FILE_MODIFIED
   *
   *  @return The current file state
  *******************************/
  s32 FileHandle::GetFileState()
  {
    return m_fileState;
  }

  /*!*****************************
   *  @brief Gets the file extension
   *
   *  @return extension as a string
  *******************************/
  std::string& FileHandle::GetFileExtension()
  {
    return m_extension;
  }

  /*!*****************************
   *  @brief Gets the file's size in bytes
   *
   *  @return filesize
  *******************************/
  u32 FileHandle::GetFileSize() const
  {
    return m_size;
  }

  s64 FileHandle::GetLastModified() const
  {
    return m_timeModified;
  }

  /*!*****************************
   *  @brief Reads in the entire file
   *
   *  @return pointer to entire file data
  *******************************/
  const char* FileHandle::ReadFile()
  {
    auto handle = std::ifstream(m_fileName, std::istream::binary | std::istream::in);
    if(m_file == nullptr)
    {
      m_file = new char[m_size];
      handle.read(m_file, m_size);
      m_readPointer = m_file;
    }

    return m_file;
  }

  /*!*****************************
   *  @brief Updates the internal file state
   *  @details Filesystem_FILE_OK, Filesystem_FILE_ERROR, or Filesystem_FILE_MODIFIED
   *
   *  @return the current filestate
  *******************************/
  s32 FileHandle::CheckFile()
  {
    struct stat attributes;

    if(stat(m_fileName.c_str(), &attributes) == -1)
    {
      m_fileState = Filesystem_FILE_ERROR;
      return m_fileState;
    }

    m_size = attributes.st_size;

    if(attributes.st_mtime > m_timeModified)
    {
      m_timeModified = attributes.st_mtime;
      m_fileState = Filesystem_FILE_MODIFIED;
      return m_fileState;
    }
    m_fileState = Filesystem_FILE_OK;
    return m_fileState;
  }
}//Filesystem
