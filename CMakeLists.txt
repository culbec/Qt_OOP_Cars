cmake_minimum_required(VERSION 3.25)
project(Qt_OOP_Cars)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "/home/culbec/Qt/6.5.0/gcc_64/lib/cmake")


find_package(Qt6 COMPONENTS
       Core
        Gui
        Widgets
       REQUIRED)

add_executable(Qt_OOP_Cars main.cpp main.cpp Sources/Car.cpp Sources/DTO.cpp Sources/Repository.cpp Sources/Service.cpp Sources/Spalatorie.cpp Sources/tests.cpp Sources/UI.cpp Sources/Validator.cpp Headers/GUI.h Sources/GUI.cpp)
target_link_libraries(Qt_OOP_Cars
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        )

