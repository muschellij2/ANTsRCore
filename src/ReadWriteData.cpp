#include "itksys/SystemTools.hxx"

#include <string>

bool ANTSFileExists(const std::string & strFilename)
{
  return itksys::SystemTools::FileExists(strFilename);
}
