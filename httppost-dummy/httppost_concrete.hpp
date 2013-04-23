#ifndef __httppost_concrete_hpp__
#define __httppost_concrete_hpp__

#include "filesys_concrete.hpp"

namespace httppost
{
  typedef filesys::Path Path;

  inline void uploadFile(Path const&) {}
}

#endif /* __httppost_concrete_hpp__ */

