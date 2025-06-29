# For a different output directory append /<directory_name> before the last quotation mark
set(output_dir "${CMAKE_BINARY_DIR}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${output_dir})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${output_dir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${output_dir})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
