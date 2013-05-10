package datasrc.DataSource
	imports lua.LuaState,
		permissions.Permissions;

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


implementation MockDataSourceMapper = {
	use Permissions;
	predicate MOCK_DATA_SOURCE_ACCESS() = Permission;
	
	
	external C++ datasrc.MockDataSourceMapper {
		require Permissions;
		require predicate MOCK_DATA_SOURCE_ACCESS();
		extend CxxLuaState;
		require type Data1;
		require type Data2;
			
		require procedure f(obs e : Entry, upd d1 : Data1, upd d2 : Data2);	
		
		type Entry;
		procedure map(upd d1 : Data1, upd d2 : Data2) 
			alert RequiresPermission pre MOCK_DATA_SOURCE_ACCESS;
	
		predicate isAccessible();
		
		procedure entryToLua(obs e : Entry, upd st : LuaState);
	};
};
