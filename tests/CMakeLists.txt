project(vuili_tests C)

# Create Window Testing Target
add_executable(test-window test-window.c)

if(LINUX)
    string(APPEND CMAKE_C_FLAGS -lm)
endif(LINUX)

# Add the src directory to the include directory list
target_include_directories(test-window PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(test-window PRIVATE vuili)
