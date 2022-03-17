cmake_minimum_required(VERSION 3.0)

project(Morskoy_Boy)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)

add_executable(main.exe main.cpp Weapons/Weapon.cpp Weapons/Projectile.cpp Ships/Ship.cpp Player/Player.cpp Field/Field.cpp)

target_link_libraries(main.exe sfml-graphics sfml-audio)