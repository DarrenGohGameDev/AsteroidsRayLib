cmake_minimum_required(VERSION 3.21)
project(MyGame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MyGame
    src/Source/Main.cpp
    src/Source/Player.cpp
    src/Source/Asteroid.cpp
    src/Source/AsteroidsManager.cpp
    src/Source/EntityTemplate.cpp
    src/Source/Movable.cpp
    src/Source/PlayerLazerProjectile.cpp
    src/Source/PlayerLazerProjectileManager.cpp
    src/Source/ScoreManager.cpp
    src/Source/GameManager.cpp
    src/Source/SaveManager.cpp
    src/Source/UIManager.cpp
    src/Source/SoundManager.cpp
    src/Source/ShootMeBtnEntity.cpp
)

# Copy Assets folder next to the executable (Debug/Release)
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/Assets
            $<TARGET_FILE_DIR:MyGame>/Assets
)

add_dependencies(MyGame copy_assets)

target_include_directories(MyGame PRIVATE src/Header)

find_package(raylib CONFIG REQUIRED)

target_link_libraries(MyGame PRIVATE raylib)