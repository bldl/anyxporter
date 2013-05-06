package engine.Engine
	imports
		lua.LuaState,
		filesys.FileSys, filesys.Bytes, filesys.Path,
		datasrc.DataSource,
		config.CurrentConfig;


concept ExportEngine = {
	type System;
	
	procedure exportData(upd sys : System);
};



program Engine = {
	use CxxFileSys;
	use CurrentConfig;
	use CxxLuaState;
	use MockDataSourceMapper[map => mapDataSource, Data1 => File, Data2 => LuaState, f => exportEntry];
	
	procedure test(upd fileSys : FileSys) {
		var st = luaState();
		var b : Bytes;
		call luaLoadFormatter(st);

		var file : File;
		call fileOpenTruncate(export_output_file, fileSys, file);

		call luaPreambleToBytes(st, b);
		call fileAppend(file, b);

		call mapDataSource(file, st);
		
		call luaPostambleToBytes(st, b);
		call fileAppend(file, b);

		call fileClose(file, fileSys); 
	}
	
	procedure exportEntry(obs e : Entry, upd file : File, upd st : LuaState) {
		call entryToLua(e, st);
		var b : Bytes;
		call luaEntryToBytes(st, b);
		call fileAppend(file, b);		
	}
};

