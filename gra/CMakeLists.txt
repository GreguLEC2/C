cmake_minimum_required(VERSION 3.5)

project(graprzygodowa VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(PROJECT_SOURCES
    main.cpp
    player.cpp
    game.cpp
    dragon.cpp
    location.cpp
    game.h
    player.h
    dragon.h
    location.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(graprzygodowa
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(graprzygodowa
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(graprzygodowa PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

set_target_properties(graprzygodowa PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(graprzygodowa)
endif()
