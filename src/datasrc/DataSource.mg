package datasrc.DataSource
	imports lua.LuaState;

concept DataSourceMapper = {
	use LuaState;
	type Entry;
	type Data1;
	type Data2;
	
	procedure map(upd d1 : Data1, upd d2 : Data2) guard isAccessible();
	procedure f(obs e : Entry, upd d1 : Data1, upd d2 : Data2);
	predicate isAccessible();
	procedure entryToLua(obs e : Entry, upd st : LuaState);
};


implementation MockDataSourceMapper = external C++ datasrc.MockDataSourceMapper {
	extend CxxLuaState;
	require type Data1;
	require type Data2;
		
	require procedure f(obs e : Entry, upd d1 : Data1, upd d2 : Data2);	
	
	type Entry;
	procedure map(upd d1 : Data1, upd d2 : Data2) guard isAccessible();

	predicate isAccessible();
	
	procedure entryToLua(obs e : Entry, upd st : LuaState);
};
