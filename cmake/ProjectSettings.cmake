if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Build type set to 'Debug' as none was specified")
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build" FORCE)
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif()

option(HEARTH_ENABLE_IPO "Enables Interprocedural Optimization, aka Link Time Optimization (LTO)" OFF)
if(HEARTH_ENABLE_IPO)
	include(CheckIPOSupported)
	check_ipo_supported(RESULT result OUTPUT output)
	if (result)
		set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
	else()
		message(SEND_ERROR "IPO is not supported: ${output}")
	endif()
endif()

function(set_project_settings project_name)
	if(CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
		set(HEARTH_DEFINITIONS ${HEARTH_DEFINITIONS} HEARTH_DEBUG=1)
	endif()

	option(HEARTH_ENABLE_PROFILING "Enables library profiling for debugging purposes." OFF)
	if(HEARTH_ENABLE_PROFILING)
		set(HEARTH_DEFINITIONS ${HEARTH_DEFINITIONS} HEARTH_PROFILE=1)
	endif()

	target_compile_definitions(${project_name} INTERFACE ${HEARTH_DEFINITIONS})
	target_compile_features(${project_name} INTERFACE cxx_std_20)
endfunction()