cmake_minimum_required(VERSION 4.0)
project(Note_App)

set(CMAKE_CXX_STANDARD 20)

add_executable(Note_App main.cpp utils/create_account.cpp utils/first_page.cpp utils/menu.cpp utils/sign_in.cpp utils/user.cpp)
