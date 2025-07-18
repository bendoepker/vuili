project(vuili C)

# Add GLFW to the library but make its symbols hidden in the case of a shared library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw)
if(BUILD_SHARED_LIBS)
    # WARN: untested
    set_property(TARGET glfw PROPERTY C_VISIBILITY_PRESET hidden)
endif()

# Vuili Source Files
set(vuili_src
    vuili.c
    utils/log.c
    glad/src/gl.c
)

list(APPEND vuili_src $<TARGET_OBJECTS:glfw>)

# Vuili Header Files
set(vuili_hdr
    vuili.h
    vuili-types.h
)

# Create the library target
add_library(vuili ${vuili_src} ${vuili_hdr})

# Set the Build Configurations
include(BuildConfig)

# Vuili Include Directories
string(APPEND
    CMAKE_C_FLAGS
    -Iglfw/include
    -Wimplicit-fallthrough
)

# Get rid of those pesky windows warnings, I know the consequences...
if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# Link the library
if(WIN32) # TODO: Only link to winmm when needed (as of right now that is when USE_HIGH_RES_TIMER == 1)
    target_link_libraries(vuili winmm)
endif()

string(APPEND CMAKE_C_FLAGS  -Isrc)

# Add the src directory to the build include so that we can use #include <vuili.h>
target_include_directories(vuili PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include
)
