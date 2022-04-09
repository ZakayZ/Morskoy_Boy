cmake_minimum_required(VERSION 3.20)

project(Morskoy_Boy)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)

include_directories(${PROJECT_SOURCE_DIR})

set(INCLUDES
        Weapons/Projectile.cpp
        Weapons/Weapon.cpp
        Ships/BoundaryBox.cpp
        Ships/Ship.cpp
        Field/Field.cpp
        Player/Player.cpp
        GameMaster/GameMaster.cpp
        Action/Action.cpp
        main.cpp)

add_executable(main.exe ${INCLUDES})

target_link_libraries(main.exe sfml-graphics)
