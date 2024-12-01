file(GLOB SOLUTION_SOURCES "*.c")

foreach(SOLUTION_SOURCE ${SOLUTION_SOURCES})
    get_filename_component(SOLUTION_NAME ${SOLUTION_SOURCE} NAME_WE)
    add_library(${SOLUTION_NAME} SHARED ${SOLUTION_SOURCE})
    set_target_properties(${SOLUTION_NAME} PROPERTIES
        OUTPUT_NAME ${SOLUTION_NAME}       # Use the filename without 'lib' prefix
        PREFIX ""                          # Remove 'lib' prefix
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} # Place .so files in build/solutions/
    )
endforeach()
