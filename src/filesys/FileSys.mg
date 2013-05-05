package filesys.FileSys
	imports luastate.LuaState;

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

implementation CxxFileSys = {
	external C++ filesys.CxxFileSys signature(FileSys);
};

