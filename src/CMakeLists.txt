
if(WIN32)
    set(exe_type WIN32)
else(APPLE)
    set(exe_type MACOSX_BUNDLE)
endif(WIN32)

add_executable(TAExecutable ${exe_type}
    utils.c
    textAdventure.c
)

find_library(READLINE_LIB readline)
message(STATUS "readline library: ${READLINE_LIB}")

target_link_libraries(TAExecutable PUBLIC
    ${READLINE_LIB}
)

SET_TARGET_PROPERTIES(TAExecutable PROPERTIES OUTPUT_NAME "Text Adventure")
