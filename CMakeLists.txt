cmake_minimum_required(VERSION 3.26)
project(Earth-vs-Aliens)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(main
Armies/AlienArmy.cpp
Armies/EarthArmy.cpp
Armies/AllyArmy.cpp
BattleUnits/AlienDrone.cpp
BattleUnits/AlienMonster.cpp
BattleUnits/AlienSoldier.cpp
BattleUnits/EarthGunnery.cpp
BattleUnits/EarthSoldier.cpp
BattleUnits/EarthTank.cpp
BattleUnits/Unit.cpp
BattleUnits/HealUnit.cpp
BattleUnits/SaverUnit.cpp
DataStructures/ArrayMonster.cpp
Game.cpp
main.cpp
RandGen.cpp)

add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/input.txt
                ${CMAKE_CURRENT_BINARY_DIR}/input.txt)