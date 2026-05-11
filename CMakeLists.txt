cmake_minimum_required(VERSION 3.16)
project(boutique_tui LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(MSVC)
  add_compile_options(/utf-8)
endif()

include(FetchContent)

FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
  GIT_TAG v6.1.9
)

FetchContent_MakeAvailable(ftxui)

add_executable(boutique_app 
    main.cpp 
    Magasin.cpp 
    Interface.cpp
)

target_link_libraries(boutique_app PRIVATE 
    ftxui::screen 
    ftxui::dom 
    ftxui::component
)















