set(CMAKE_CXX_STANDARD 20)

project(query)
set(SOURCES QueryMaker.cpp)
set(HEADERS QueryMaker.h)
add_library(QueryMaker ${SOURCES} ${HEADERS})
#target_link_libraries(GameXO PUBLIC game)
target_include_directories(GameXO PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})