cmake_minimum_required(VERSION 3.21)

project(Morskoy_Boy)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(main.exe Weapons/Projectile.h Weapons/Weapon.h Ships/BoundaryBox.h Ships/Ship.h Field/Field.h Player/Player.h Weapons/Projectile.cpp Weapons/Weapon.cpp Ships/BoundaryBox.cpp Ships/Ship.cpp Field/Field.cpp Player/Player.cpp main.cpp)

target_link_libraries(main.exe sfml-graphics)