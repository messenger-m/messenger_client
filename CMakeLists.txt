cmake_minimum_required(VERSION 3.19)
project(messenger_client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

find_package(Protobuf REQUIRED)

find_package(gRPC CONFIG REQUIRED)

qt_add_executable(messenger_client
    WIN32 MACOSX_BUNDLE

    src/main.cpp

    src/ui/mainwindow.cpp
    src/ui/mainwindow.h
    src/ui/mainwindow.ui

    src/ui/loginwindow.cpp
    src/ui/loginwindow.h
    src/ui/loginwindow.ui

    src/ui/registerdialog.cpp
    src/ui/registerdialog.h
    src/ui/registerdialog.ui

    src/grps/authclient.cpp
    src/grps/authclient.h

    generated/auth.grpc.pb.h
    generated/auth.pb.h
    generated/auth.grpc.pb.cc
    generated/auth.pb.cc
    .gitignore

)
target_include_directories(messenger_client PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/generated
)

target_link_libraries(
    messenger_client PRIVATE
    Qt6::Core
    Qt6::Widgets
    gRPC::grpc++
    protobuf::libprotobuf
)

qt_standard_project_setup()
