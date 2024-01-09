cmake_minimum_required(VERSION 3.19)
project(notes)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_PREFIX_PATH "D:/Qt/5.15.2/mingw81_64")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets Network PrintSupport)  # 添加 Network 模块
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network Qt5::PrintSupport)  # 添加 Network 模块
set(CMAKE_PREFIX_PATH "D:/Qt/5.15.2/mingw81_64")

add_definitions(-DAPP_QT_VERSION=\"${QT_VERSION}\")
add_definitions(
        -DAPP_PRODUCT="QText"
        -DAPP_COMPANY="TangWenQian"
        -DAPP_VERSION="1.0.0"
        -DAPP_COPYRIGHT="2021414120219 work"
        -DAPP_DESCRIPTION="QText: Note taking utility with auto-save"
)


add_executable(${PROJECT_NAME}
        icons
        medo/about.h
        medo/appsetupmutex.h
        medo/config.h
        medo/dconfHotkey.h
        medo/feedback.h
        medo/hotkey.h
        medo/hotkey.cpp
        medo/about.cpp
        medo/appsetupmutex.cpp
        medo/config.cpp
        medo/dconfHotKey.cpp
        medo/feedback.cpp
        ui/finddialog.cpp
        ui/finddialog.h
        ui/foldersdialog.cpp
        ui/foldersdialog.h
        ui/gotodialog.cpp
        ui/gotodialog.h
        ui/hotkeyedit.cpp
        ui/hotkeyedit.h
        ui/inserttimedialog.cpp
        ui/inserttimedialog.h
        ui/settingsdialog.cpp
        ui/settingsdialog.h
        ui/mainwindow.cpp
        ui/mainwindow.h
        ui/newfiledialog.cpp
        ui/newfiledialog.h
        ui/qtabbarex.cpp
        ui/qtabbarex.h
        ui/qtabwidgetex.cpp
        ui/qtabwidgetex.h
        ui/phoneticdialog.cpp
        ui/phoneticdialog.h
        ui/renamefiledialog.cpp
        ui/renamefiledialog.h
        medo/lifetimewatch.cpp
        medo/lifetimewatch.h
        medo/singleinstance.cpp
        medo/singleinstance.h
        medo/state.cpp
        medo/state.h
        medo/upgrade.cpp
        medo/upgrade.h
        storage/fileitem.cpp
        storage/fileitem.h
        storage/folderitem.cpp
        storage/folderitem.h
        storage/storage.cpp
        storage/storage.h
        storage/storagemonitorlocker.cpp
        storage/storagemonitorlocker.h
        storage/storagemonitorthread.cpp
        storage/storagemonitorthread.h
        app.cpp
        clipboard.cpp
        clipboard.h
        deletion.cpp
        deletion.h
        find.cpp
        find.h
        helpers.cpp
        helpers.h
        icons.cpp
        icons.h
        phoneticalphabet.cpp
        phoneticalphabet.h
        rtfconverter.cpp
        rtfconverter.h
        settings.cpp
        settings.h
        setup.cpp
        setup.h
        medo/dconfHotkey.cpp
        medo/dconfHotkey.h
        medo/winHotkey.cpp
        medo/winHotkey.h
        ui/finddialog.ui
        ui/foldersdialog.ui
        ui/gotodialog.ui
        ui/inserttimedialog.ui
        ui/newfiledialog.ui
        ui/phoneticdialog.ui
        ui/renamefiledialog.ui
        ui/settingsdialog.ui
        ui/mainwindow.ui)

# 添加头文件路径
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})


if (WIN32)

    set(DEBUG_SUFFIX)
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "")  # 此处去掉""d
    endif ()

    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB ${REQUIRED_LIBS})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt${QT_VERSION}${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()

