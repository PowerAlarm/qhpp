cmake_minimum_required(VERSION 3.19)
project(qhpp LANGUAGES CXX)

find_package(Qt6 6.9 REQUIRED COMPONENTS Core Widgets Network LinguistTools)

qt_standard_project_setup()

qt_add_executable(qhpp
    WIN32 MACOSX_BUNDLE
    main.cpp
    foablak.cpp
    foablak.h
    foablak.ui
    sitesearch.ui
    sitesearch.h
    sitesearch.cpp
    sitelistmodel.h sitelistmodel.cpp
    devicelist.h devicelist.cpp devicelist.ui
    devicelistmodel.h devicelistmodel.cpp
)

qt_add_translations(
    TARGETS qhpp
    TS_FILES qhpp_hu_HU.ts
)

target_link_libraries(qhpp
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
)

include(GNUInstallDirs)

install(TARGETS qhpp
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET qhpp
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
