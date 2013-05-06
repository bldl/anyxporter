// implementation: implementation filesys.FileSys.CxxFileSys, file: "filesys/CxxFileSys.hxx" 
#ifndef _INCLUDE_FILESYS_CXXFILESYS_HXX
#define _INCLUDE_FILESYS_CXXFILESYS_HXX

#include <iostream>
namespace filesys {
struct CxxFileSys {
	struct CxxFileSys_impl {
		typedef std::string Bytes;
		typedef std::string Path;

		struct File {
			std::ofstream stream;

		public:
			File() = default;
			File(const File&) {
				throw "Files can't be copied";
			}
			~File() = default;
			File& operator=(const File&) = default;
			bool operator==(const File& _other) {
				
				return true;
			}
			template<typename _Stream> void operator>>=(_Stream& _stream) const {
				Magnolia::IO::Type _type_tag = Magnolia::IO::Type("File", "");
				
				Magnolia::IO::startData(_type_tag) >>= _stream;
				
				Magnolia::IO::endData(_type_tag) >>= _stream;
			}
			template<typename _Stream> void operator<<=(_Stream& _stream) {
				Magnolia::IO::Type _type_tag = Magnolia::IO::Type("File", "");
				
				Magnolia::IO::startData(_type_tag) <<= _stream;
				
				Magnolia::IO::endData(_type_tag) <<= _stream;
			}
		};
		
		
		
		struct FileSys {
		public:
			FileSys() = default;
			FileSys(const FileSys&) {
				throw "File systems can't be copied";
			}
			~FileSys() = default;
			FileSys& operator=(const FileSys&) = default;
			bool operator==(const FileSys& _other) {
				
				return true;
			}
			template<typename _Stream> void operator>>=(_Stream& _stream) const {
				Magnolia::IO::Type _type_tag = Magnolia::IO::Type("FileSys", "");
				
				Magnolia::IO::startData(_type_tag) >>= _stream;
				
				Magnolia::IO::endData(_type_tag) >>= _stream;
			}
			template<typename _Stream> void operator<<=(_Stream& _stream) {
				Magnolia::IO::Type _type_tag = Magnolia::IO::Type("FileSys", "");
				
				Magnolia::IO::startData(_type_tag) <<= _stream;
				
				Magnolia::IO::endData(_type_tag) <<= _stream;
			}
		};
		
		
		/** procedure fileAppend(upd :File, obs :Bytes) */
		void fileAppend(File& file, const Bytes& s) const {
			file.stream << s;
		}
		
		/** procedure fileClose(upd :File, upd :FileSys) */
		void fileClose(File& file, FileSys& fileSys) const {
			file.stream.close();
		}
		
		/** procedure fileOpenTruncate(obs :Path, upd :FileSys, out :File) */
		void fileOpenTruncate(const Path& path, FileSys& fileSys, File& file) const {
			if(file.stream.is_open())
				file.stream.close();
			file.stream.open(path, std::ifstream::out);
		}
	};
	
	
};


}


#endif
