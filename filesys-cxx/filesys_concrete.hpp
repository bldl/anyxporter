#ifndef __filesys_concrete_hpp__
#define __filesys_concrete_hpp__

#include <fstream>
#include <string>

namespace dataout
{
  typedef char const* Path;

  // Dtor closes any open stream, presumably throwing an exception on
  // 'close' error. Should we want tempfile support, would probably
  // have to use a RAII wrapper to do deletion, using 'remove',
  // probably storing filename in a std::string.
  typedef std::ofstream File;

  typedef char const* Bytes;
  typedef std::streamsize NumBytes;
}

#endif /* __filesys_concrete_hpp__ */
