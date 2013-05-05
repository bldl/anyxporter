// implementation: implementation luastate.LuaState.CxxLuaState, file: "luastate/CxxLuaState.hxx" 
#ifndef _INCLUDE_LUASTATE_CXXLUASTATE_HXX
#define _INCLUDE_LUASTATE_CXXLUASTATE_HXX
#include "abstract.hpp"

#include "current_config.hrh"

#include <stdexcept>

#include <assert.h>

template<typename _Stream> void operator>>=(const std::string& bytes, _Stream& _stream) {
	Magnolia::IO::Type _type_tag = Magnolia::IO::Type("String", "");

	Magnolia::IO::startData(_type_tag) >>= _stream;
	_stream.stream << bytes;
	Magnolia::IO::endData(_type_tag) >>= _stream;
}
template<typename _Stream> void operator<<=(std::string& bytes, _Stream& _stream) {
	Magnolia::IO::Type _type_tag = Magnolia::IO::Type("String", "");

	Magnolia::IO::startData(_type_tag) <<= _stream;
	_stream.stream >> bytes;
	Magnolia::IO::endData(_type_tag) <<= _stream;
}

template<typename _Stream> void operator>>=(const luastate::LuaState& st, _Stream& _stream) {
	Magnolia::IO::Type _type_tag = Magnolia::IO::Type("LuaState", "");

	Magnolia::IO::startData(_type_tag) >>= _stream;
//	_stream.stream << st;
	Magnolia::IO::endData(_type_tag) >>= _stream;
}
template<typename _Stream> void operator<<=(luastate::LuaState& st, _Stream& _stream) {
	Magnolia::IO::Type _type_tag = Magnolia::IO::Type("LuaState", "");

	Magnolia::IO::startData(_type_tag) <<= _stream;
//	_stream.stream >> st;
	Magnolia::IO::endData(_type_tag) <<= _stream;
}

namespace lua {


struct CxxLuaState {
	struct CxxLuaState_impl {
		typedef std::string Bytes;
		typedef luastate::LuaState LuaState;

		void luaState(LuaState& st) const {
			luastate::init(st);
		}

		/** procedure luaEntryToBytes(upd :LuaState, out :Bytes) */
		void luaEntryToBytes(LuaState& st, Bytes& s) const {
			filesys::luaEntryToBytes(st, s);
		}

		/** procedure luaLoadFormatter(upd :LuaState) */
		void luaLoadFormatter(LuaState& st) const {
			filesys::luaLoadFormatter(st);
		}

		/** procedure luaPostambleToBytes(upd :LuaState, out :Bytes) */
		void luaPostambleToBytes(LuaState& st, Bytes& s) const {
			filesys::luaPostambleToBytes(st, s);
		}

		/** procedure luaPreambleToBytes(upd :LuaState, out :Bytes) */
		void luaPreambleToBytes(LuaState& st, Bytes& s) const {
			filesys::luaPreambleToBytes(st, s);
		}
	};


};


}


#endif
