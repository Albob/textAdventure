
if(WIN32)
    set(exe_type WIN32)
else(APPLE)
    set(exe_type MACOSX_BUNDLE)
endif(WIN32)

add_executable(TAExecutable ${exe_type}
    utils.c
    textAdventure.c
)
SET_TARGET_PROPERTIES(TAExecutable PROPERTIES OUTPUT_NAME "Text Adventure")
