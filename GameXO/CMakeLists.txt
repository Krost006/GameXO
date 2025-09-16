# CMakeList.txt: проект CMake для GameXO; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
set(CMAKE_CXX_STANDARD 20)
# Добавьте источник в исполняемый файл этого проекта.
add_executable (GameXO "GameXO.cpp" "GameXO.h" "Game/Game.cpp" "Game/Game.h" "NetCode/Net.cpp" "NetCode/Net.h"  "QueryMaker/QueryMaker.cpp" "QueryMaker/QueryMaker.h")

#add_executable(Client client.cpp)

#include_directories(Game)
add_subdirectory(Game)
add_subdirectory(NetCode)
add_subdirectory(QueryMaker)

target_link_libraries(GameXO net game wsock32 ws2_32)

#add_library(game Game/Game.cpp Game/Game.h)

#install(game)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GameXO PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
