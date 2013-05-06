// implementation: implementation config.CurrentConfig.CurrentConfig, file: "config/CurrentConfig.hxx" 
#ifndef _INCLUDE_CONFIG_CURRENTCONFIG_HXX
#define _INCLUDE_CONFIG_CURRENTCONFIG_HXX
#include <string>
#include "current_config.hrh"

namespace config {
struct CurrentConfig {
	struct CurrentConfig_impl {
		typedef std::string Bytes;
		typedef std::string Path;

		/** function APP_BASENAME() : Bytes */
		Bytes app_basename() const {
			// TODO: auto-generated function stub
			return APP_BASENAME;
		}
		
		/** function APP_LONG_NAME() : Bytes */
		Bytes app_long_name() const {
			return APP_LONG_NAME;
		}
		
		/** function APP_NAME() : Bytes */
		Bytes app_name() const {
			return APP_NAME;
		}
		
		/** function APP_SHORT_NAME() : Bytes */
		Bytes app_short_name() const {
			return APP_SHORT_NAME;
		}
		
		/** function EXPORT_OUTPUT_FILE() : Path */
		Path export_output_file() const {
			return EXPORT_OUTPUT_FILE;
		}
		
		/** predicate FEATURE_DEBUGGING() */
		bool feature_debugging() const {
			return FEATURE_DEBUGGING;
		}
		
		/** predicate FEATURE_GUI() */
		bool feature_gui() const {
			return FEATURE_GUI;
		}
		
		/** predicate FEATURE_HTTP_POST() */
		bool feature_http_post() const {
			return FEATURE_HTTP_POST;
		}
		
		/** predicate IS_DEVICE() */
		bool is_device() const {
			return IS_DEVICE;
		}
		
		/** predicate IS_HARMATTAN() */
		bool is_harmattan() const {
			return IS_HARMATTAN;
		}
		
		/** predicate IS_QT_SIMULATOR() */
		bool is_qt_simulator() const {
			return IS_QT_SIMULATOR;
		}
		
		/** predicate IS_SYMBIAN() */
		bool is_symbian() const {
			return IS_SYMBIAN;
		}
		
		/** function PLATFORM_STR() : Bytes */
		Bytes platform_str() const {
			return PLATFORM_STR;
		}
		
		/** function VARIANT_NAME() : Bytes */
		Bytes variant_name() const {
			return VARIANT_NAME;
		}
		
		/** function VENDOR_NAME() : Bytes */
		Bytes vendor_name() const {
			return VENDOR_NAME;
		}
		
		/** predicate VERSION100() */
		bool version100() const {
			return VERSION100;
		}
		
		/** function VERSION_STRING() : Bytes */
		Bytes version_string() const {
			return VERSION_STRING;
		}
	};
	
	
};


}


#endif
