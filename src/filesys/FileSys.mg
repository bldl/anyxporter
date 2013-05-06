package filesys.FileSys
	imports lua.LuaState, filesys.Bytes, filesys.Path, config.CurrentConfig;

/*
concept FileSys = {
	use LuaState;
		
	type Path;
	type FileSys;
	type File;
	type Bytes;
		
	procedure fileOpenTruncate(obs path : Path, upd fileSys : FileSys, out file : File);
	procedure fileClose(upd file : File, upd fileSys : FileSys);
	procedure fileAppend(upd file: File, obs s : Bytes);
};
*/

implementation CxxFileSys = external C++ filesys.CxxFileSys {
	extend CxxLuaState;
	extend CxxPath;
	
	type Path;
	type FileSys;
	type File;
	type Bytes;
		
	procedure fileOpenTruncate(obs path : Path, upd fileSys : FileSys, out file : File);
	procedure fileClose(upd file : File, upd fileSys : FileSys);
	procedure fileAppend(upd file: File, obs s : Bytes);
};


program FileSysTest = {
	use CxxFileSys;
	use CurrentConfig;
	
	procedure test(upd fileSys : FileSys) {
		var file : File;
		call fileOpenTruncate(export_output_file, fileSys, file);
		call fileAppend(file, app_basename);
		call fileClose(file, fileSys); 
	}
};

