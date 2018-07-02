find_library(GLOG_LIBRARY NAMES libglog.a HINTS /home/lzy/car_cc/lib) 

get_filename_component(_libdir "${GLOG_LIBRARY}" PATH)

find_path(GLOG_INCLUDE_DIR NAMES logging.h PATHS /home/lzy/car_cc/include/glog NO_DEFAULT_PATH) 

set(_deps_check)
get_filename_component(GLOG_RUNTIME_LIBRARY_DIRS
	"${GLOG_LIBRARY}"
	PATH)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(GLOG
	DEFAULT_MSG
	GLOG_LIBRARY
	GLOG_INCLUDE_DIR
	${_deps_check})
#message("Found headers in: ${GLOG_INCLUDE_DIR}")

if(GLOG_FOUND)
	set(GLOG_LIBRARIES "${GLOG_LIBRARY}")
	set(GLOG_INCLUDE_DIRS "${GLOG_INCLUDE_DIR}")
	mark_as_advanced(GLOG_ROOT_DIR)
endif()

mark_as_advanced(GLOG_INCLUDE_DIR
	GLOG_LIBRARY
	GLOG_RUNTIME_LIBRARY)
