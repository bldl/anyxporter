package config.CurrentConfig
	imports filesys.Bytes, filesys.Path;

implementation CurrentConfig = external C++ config.CurrentConfig {
	extend CxxPath;
	extend CxxBytes;
	
	function app_basename() : Bytes;
	function app_long_name() : Bytes;
	function app_name() : Bytes;
	function app_short_name() : Bytes;
	function export_output_file() : Path;
	predicate feature_debugging();
	predicate feature_gui();
	predicate feature_http_post();
	predicate is_device();
	predicate is_harmattan();
	predicate is_qt_simulator();
	predicate is_symbian();
//	function major_version() : Integer;
//	function minor_version() : Integer;
	function platform_str() : Bytes;
	function variant_name() : Bytes;
	function vendor_name() : Bytes;
	function version_string() : Bytes;
	predicate version100();
};
