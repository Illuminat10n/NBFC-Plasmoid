# TODO: adapt "org.kde.plasma" here & elsewhere if needed (see README)
add_definitions(-DTRANSLATION_DOMAIN=\"plasma_applet_org.kde.plasma.omenctlnew\")

add_library(org.kde.plasma.omenctlnew MODULE omenctl.h omenctl.cpp fan.h fan.cpp fanmodel.h fanmodel.cpp)

include_directories(${Plasma_INCLUDE_DIRS})
include_directories(/usr/include/Plasma)

target_link_libraries(org.kde.plasma.omenctlnew
                      Qt6::Gui
                      Qt6::Qml
                      Plasma
                      KF6::I18n
                      KF6::AuthCore
                      KF6::ConfigCore
)

#ecm_add_qml_module(org.kde.plasma.omenctlnew URI org.kde.plasma.omenctlnew GENERATE_PLUGIN_SOURCE)

install(TARGETS org.kde.plasma.omenctlnew DESTINATION ${KDE_INSTALL_PLUGINDIR}/plasma/applets)

plasma_install_package(package org.kde.plasma.omenctlnew)

add_executable(omenctlnew_helper roothelper.h roothelper.cpp)

target_link_libraries(omenctlnew_helper
                        KF6::AuthCore
                        Qt6::Core
                     )
install(TARGETS omenctlnew_helper DESTINATION ${KAUTH_HELPER_INSTALL_DIR})

kauth_install_helper_files(omenctlnew_helper org.kde.plasma.omenctlnew root)
kauth_install_actions(org.kde.plasma.omenctlnew setfanspeed.txt)

