cmake_minimum_required(VERSION 3.16)

project(ClipUUID VERSION 0.1 LANGUAGES CXX)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Widgets)

qt_standard_project_setup(REQUIRES 6.5)

add_subdirectory(lib/libuiohook)

qt_add_executable(clipuuid
    src/main.cpp
    resources.qrc
)

qt_add_qml_module(clipuuid
    URI clipuuid
    VERSION 1.0
    QML_FILES
        src/Main.qml
        SOURCES src/uuidgenorator.h src/uuidgenorator.cpp
        SOURCES src/inputhandler.h src/inputhandler.cpp
        SOURCES src/clipuuid.h src/clipuuid.cpp
        SOURCES src/aboutqtdialog.h src/aboutqtdialog.cpp
        RESOURCES resources.qrc
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(clipuuid PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.clipuuid
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    OUTPUT_NAME ClipUUID
)

target_link_libraries(clipuuid
    PRIVATE Qt6::Quick Qt6::Widgets uiohook
)

include(GNUInstallDirs)
install(TARGETS clipuuid
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
