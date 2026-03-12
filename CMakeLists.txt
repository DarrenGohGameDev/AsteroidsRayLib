cmake_minimum_required(VERSION 3.21)
project(Asteroid)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Asteroid WIN32
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
            $<TARGET_FILE_DIR:Asteroid>/Assets
)

add_dependencies(Asteroid copy_assets)

target_include_directories(Asteroid PRIVATE src/Header)

find_package(raylib CONFIG REQUIRED)

target_link_libraries(Asteroid PRIVATE raylib)