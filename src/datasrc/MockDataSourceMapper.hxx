// implementation: implementation datasrc.DataSource.MockDataSourceMapper, file: "datasrc/MockDataSourceMapper.hxx" 
#ifndef _INCLUDE_DATASRC_MOCKDATASOURCEMAPPER_HXX
#define _INCLUDE_DATASRC_MOCKDATASOURCEMAPPER_HXX
#include "abstract.hpp"

namespace datasrc {
template<typename _Stream> void operator>>=(const datasrc::Entry& entry, _Stream& _stream) {
	Magnolia::IO::Type _type_tag = Magnolia::IO::Type("Entry", "");

	Magnolia::IO::startData(_type_tag) >>= _stream;
//	entry.firstName >>= _stream;
//	entry.lastName >>= _stream;
	Magnolia::IO::endData(_type_tag) >>= _stream;
}
template<typename _Stream> void operator<<=(datasrc::Entry& entry, _Stream& _stream) {
	Magnolia::IO::Type _type_tag = Magnolia::IO::Type("Entry", "");

	Magnolia::IO::startData(_type_tag) <<= _stream;
//	entry.firstName <<= _stream;
//	entry.lastName <<= _stream;
	Magnolia::IO::endData(_type_tag) <<= _stream;
}

template<typename DATA1, typename DATA2>
struct MockDataSourceMapper {
	template<typename F_OP>
	struct MockDataSourceMapper_impl {
		typedef datasrc::Entry Entry;

		/** require procedure f(obs :Entry) */
		const F_OP& f;
		
		MockDataSourceMapper_impl(const F_OP& _f)
			: f(_f)
			{};
		
		/** predicate isAccessible() */
		bool isAccessible() const {
			return true;
		}
		
		/** procedure map() */
		void map(DATA1& d1, DATA2& d2) const {
		    datasrc::Db db;
		    datasrc::open(db);
		    datasrc::Iter iter;
		    datasrc::iterator(db, iter);
		    bool r;
		    datasrc::atEof(iter, r);
		    while(!r) {
		      datasrc::Entry e;
		      datasrc::next(iter, e);
		      f(e, d1, d2);
		      datasrc::atEof(iter, r);
		    }
		    datasrc::close(db);
		}

		void entryToLua(const Entry& e, luastate::LuaState& L) const {
			datasrc::entryToLua(0, e, L);
		}
	};
	
	
};


}


#endif
