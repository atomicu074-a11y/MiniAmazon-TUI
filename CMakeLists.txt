cmake_minimum_required(VERSION 3.16)
project(jeu_combat LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
  GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(ftxui)

add_executable(combat_app 
    main.cpp 
    GAME.cpp   # يمثل ملف المنطق البرمجي للعبة
    Interface.cpp # ملف الواجهة الرسومية Text-based
)

target_link_libraries(combat_app PRIVATE 
    ftxui::screen 
    ftxui::dom 
    ftxui::component
)











