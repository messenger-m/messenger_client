cmake_minimum_required(VERSION 3.19)
project(messengerDesktop LANGUAGES CXX)

find_package(Qt6 6.10 REQUIRED COMPONENTS Core Widgets WebSockets)

qt_standard_project_setup()

qt_add_executable(messengerDesktop
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    authservice.h
    authservice.cpp
    chatclient.h
    chatclient.cpp
)

target_link_libraries(messengerDesktop
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::WebSockets
)

include(GNUInstallDirs)

install(TARGETS messengerDesktop
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET messengerDesktop
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
