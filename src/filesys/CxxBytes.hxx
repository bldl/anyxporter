// implementation: implementation filesys.FileSys.CxxPath, file: "filesys/Path.hxx" 
#ifndef _INCLUDE_FILESYS_BYTES_HXX
#define _INCLUDE_FILESYS_BYTES_HXX
#include <string>
namespace filesys {
struct CxxBytes {
	struct CxxBytes_impl {
		typedef std::string Bytes;
	};
};
}


#endif
