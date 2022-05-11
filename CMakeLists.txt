cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INSTALL_PREFIX $ENV{HOME}/.lv2/lvhelp_example_plugins.lv2)

project(LVHelpExamples VERSION 0.1.0)
set(PROJECT_IRI "http://github.com/SmoothProcess/lvhelp-examples")

set(AUTHOR_IRI "http://github.com/SmoothProcess")
set(AUTHOR_NAME "Rui Costa (SmoothProcess)")
set(AUTHOR_EMAIL "--no-email--")
set(AUTHOR_HOMEPAGE "http://github.com/SmoothProcess")

add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wnon-virtual-dtor)

include_directories(
	lvhelp/include
	magic_get/include
	lvtk
	${CMAKE_BINARY_DIR}
)


add_library(volume_example SHARED volume_example.cpp)
add_executable(ttl_generator ttl_generator.cpp)


set_target_properties(volume_example PROPERTIES PREFIX "")
set_target_properties(volume_example PROPERTIES SUFFIX ${CMAKE_SHARED_LIBRARY_SUFFIX})

get_target_property(TARGET_PREFIX volume_example PREFIX)
get_target_property(TARGET_NAME volume_example NAME)
get_target_property(TARGET_SUFFIX volume_example SUFFIX)

set(TARGET_FULL_NAME ${TARGET_PREFIX}${TARGET_NAME}${TARGET_SUFFIX})

set(PLUGIN_IRI "http://github.com/SmoothProcess/lvhelp-example")
set(PLUGIN_NAME "LVhelp Volume Example")


configure_file(config.hpp.in config.hpp)



set(TTL_NAME ${TARGET_NAME}.ttl)

add_custom_command(
	TARGET volume_example
	POST_BUILD
	COMMAND ttl_generator "manifest.ttl" "${TTL_NAME}"
	DEPENDS ttl_generator
	COMMENT "Generate ttl files"
)


# optional
find_program(LV2LINT lv2lint)
if(LV2LINT)
	set(LV2LINT_FLAGS "-E warn -E note")
	add_custom_target(
		lv2lint_validate
		DEPENDS test_plugin
		COMMAND ${LV2LINT} -I ${PROJECT_BINARY_DIR} ${LV2LINT_FLAGS} ${PLUGIN_IRI}
		COMMENT "Verify plugin and manifest using lv2lint. Note that only the first IRI match will be verified."
	)
else()
	message("NOTE: lv2lint not found. Consider installing it: https://open-music-kontrollers.ch/lv2/lv2lint/")
endif()


install(TARGETS volume_example DESTINATION .)
install(
	FILES
		${PROJECT_BINARY_DIR}/manifest.ttl
		${PROJECT_BINARY_DIR}/${TTL_NAME}
	DESTINATION .
)