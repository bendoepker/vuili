set(CMAKE_BUILD_TYPE Debug)

# Set the library to use PIC when building a shared library
if(BUILD_SHARED_LIBS)
    set_property(TARGET vuili PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

# Set the C Standard
set(CMAKE_C_STANDARD 23)

# Add Compiler Flags
target_compile_options(vuili PRIVATE
    -Wimplicit-fallthrough
)

# Add Linker Flags
target_link_options(vuili PRIVATE

)
