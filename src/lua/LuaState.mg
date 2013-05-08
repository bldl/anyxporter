package lua.LuaState
	imports filesys.Bytes;

concept LuaState = {
	type LuaState;
	type Bytes;
	
	procedure luaState(out st : LuaState);
	procedure luaLoadFormatter(upd st : LuaState);
	procedure luaPreambleToBytes(upd st : LuaState, out s : Bytes);
	procedure luaPostambleToBytes(upd st : LuaState, out s : Bytes);
	procedure luaEntryToBytes(upd st : LuaState, out s : Bytes);	
};

implementation CxxLuaState = external C++ lua.CxxLuaState {
	extend CxxBytes;
	
	type LuaState;

	procedure luaState(out st : LuaState);
	procedure luaLoadFormatter(upd st : LuaState);
	procedure luaPreambleToBytes(upd st : LuaState, out s : Bytes);
	procedure luaPostambleToBytes(upd st : LuaState, out s : Bytes);
	procedure luaEntryToBytes(upd st : LuaState, out s : Bytes);	
};


program LuaStateTest = {
	use CxxLuaState;
};
