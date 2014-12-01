cmake_minimum_required(VERSION 2.8.12)

set(APPLICATION_SOURCES
  "${CMAKE_CURRENT_LIST_DIR}/main.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/../vendor/jsoncpp/jsoncpp.cpp"
)

SET(LIBS
)


add_executable(bench-bin ${APPLICATION_SOURCES})
set_target_properties(bench-bin
    PROPERTIES
    OUTPUT_NAME bench
    CLEAN_DIRECT_OUTPUT 1
)
target_link_libraries(bench-bin ${LIBS})

install(TARGETS bench-bin DESTINATION bin)
