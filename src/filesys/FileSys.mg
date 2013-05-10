package filesys.FileSys
	imports 
		lua.LuaState, 
		filesys.Bytes, filesys.Path,
		permissions.Permissions,
		config.CurrentConfig
		;

concept FileSys = {		
	type Path;
	type FileSys;
	type File;
	type Bytes;
		
	procedure fileOpenTruncate(obs path : Path, upd fileSys : FileSys, out file : File);
	procedure fileClose(upd file : File, upd fileSys : FileSys);
	procedure fileAppend(upd file: File, obs s : Bytes);
};

implementation CxxFileSysPermissions = {
	use Permissions;
	
	predicate CXX_FILE_CREATE() = Permission;
	predicate CXX_FILE_WRITE() = Permission;
	predicate CXX_FILE_READ() = Permission;
	predicate CXX_FILE_DELETE() = Permission;
};


implementation CxxFileSys = {
	use CxxFileSysPermissions;
		
	external C++ filesys.CxxFileSys {
		require signature(CxxFileSysPermissions);
		extend CxxPath;
		extend CxxBytes;
		
		type Path;
		type FileSys;
		type File;
			
		procedure fileOpenTruncate(obs path : Path, upd fileSys : FileSys, out file : File)
			alert RequiresPermission unless pre CXX_FILE_CREATE && CXX_FILE_WRITE;
		procedure fileClose(upd file : File, upd fileSys : FileSys);
		procedure fileAppend(upd file: File, obs s : Bytes);
	};
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

