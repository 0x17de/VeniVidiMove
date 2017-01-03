cmake_minimum_required(VERSION 3.0)
project(VeniVidiMove)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Widgets)

if(UNIX)
  find_package(PkgConfig)
  pkg_check_modules(POPPLER-QT5 REQUIRED poppler-qt5>=0.25.0)
else()
  set(POPPLER-QT5_INCLUDE_DIRS "POPPLER-QT5-NOTFOUND" CACHE STRING "Path to the poppler sources")
  set(POPPLER-QT5_LIBRARIES "POPPLER-QT5-NOTFOUND" CACHE STRING "Path to the poppler-qt5 library")
endif()

set(SOURCES src/version.hpp
  src/main.cpp src/GlobalData.hpp
  src/MainWindow.cpp src/MainWindow.hpp
  src/Utils.cpp src/Utils.hpp
)

add_executable(VeniVidiMove WIN32 ${SOURCES})

target_include_directories(VeniVidiMove PUBLIC "${POPPLER-QT5_INCLUDE_DIRS}")
link_directories("${POPPLER-QT5_LIBRARY_DIRS}")
target_link_libraries(VeniVidiMove Qt5::Widgets "${POPPLER-QT5_LIBRARIES}")

if(UNIX)
  set_target_properties(VeniVidiMove PROPERTIES COMPILE_FLAGS "-std=c++11 -pedantic -Wall")
endif()


# VERSION INFORMATION
file(STRINGS src/version.hpp VERSION)
string(REPLACE " " ";" VERSION "${VERSION}")
list(LENGTH VERSION VERSION_LEN)
list(GET VERSION 4 CPACK_PACKAGE_VERSION_MAJOR)
list(GET VERSION 10 CPACK_PACKAGE_VERSION_MINOR)
list(GET VERSION 16 CPACK_PACKAGE_VERSION_PATCH)
set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
message("VeniVidiMove Version ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

# INSTALL SETTINGS
install(TARGETS VeniVidiMove
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION bin)
include(InstallRequiredSystemLibraries)
install(PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS}
        DESTINATION bin COMPONENT runtime)

# OS SPECIFIC INSTALL SETTINGS
if(WIN32)
  # INCLUDE LIBRARIES IF PRESENT
  SET(CPACK_GENERATOR "NSIS")
  FILE(GLOB EXT_DLLS "ext/*.dll")
  if(EXT_DLLS)
    install(FILES ${EXT_DLLS}
            DESTINATION bin)
  endif()
  SET(CPACK_NSIS_CONTACT "Manuel Herrmann <m@manuel-herrmann.de>")
  SET(CPACK_NSIS_URL_INFO_ABOUT "https://www.manuel-herrmann.de")
elseif(UNIX)
  SET(CPACK_GENERATOR "DEB;TGZ")
  SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Manuel Herrmann")
endif()
SET(CPACK_PACKAGE_EXECUTABLES "VeniVidiMove" "VeniVidiMove")

include(CPack)

