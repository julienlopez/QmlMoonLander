cmake_minimum_required(VERSION 3.5)

project(QmlMoonLander LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TODO clean up
set(ML_BOOST_ROOT_DIR "" CACHE PATH "Use specific boost folder?")
if(NOT "${ML_BOOST_ROOT_DIR}" STREQUAL "")
        include_directories("${ML_BOOST_ROOT_DIR}")
        #link_directories("${ML_BOOST_ROOT_DIR}/stage/lib")
endif()

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

file (GLOB SRC_FILES src/*)

if(ANDROID)
    add_library(QmlMoonLander SHARED ${SRC_FILES} qml.qrc images.qrc)
else()
    add_executable(QmlMoonLander ${SRC_FILES} qml.qrc images.qrc)
endif()

target_compile_definitions(QmlMoonLander
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(QmlMoonLander
  PRIVATE Qt5::Core Qt5::Quick)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# These variables must use CACHE, otherwise QtCreator won't see them.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android" CACHE INTERNAL "")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so CACHE INTERNAL "")
#    endif()
#endif()

