cmake_minimum_required(VERSION 3.16)

project(plasma-omenctlnew)

set(QT_MIN_VERSION "6.6.0")
set(QT_VERSION_MAJOR "6")
set(KF6_MIN_VERSION "6.0.0")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)

add_definitions(-DQT_QML_DEBUG)

find_package(ECM ${KF6_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)

include(ECMQtDeclareLoggingCategory)
include(ECMGenerateExportHeader)
include(ECMInstallIcons)
include(KDEPackageAppTemplates)
include(GenerateExportHeader)
include(CMakePackageConfigHelpers)
include(KDEClangFormat)
include(KDEGitCommitHooks)
include(ECMDeprecationSettings)
include(ECMQmlModule)

find_package(Plasma ${KF6_MIN_VERSION} REQUIRED)
include_directories(/usr/include/Plasma)
find_package(KF6 ${KF6_MIN_VERSION} REQUIRED COMPONENTS
    I18n
    KIO
    Auth
    Config
)

find_package(Qt6 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
    Quick
    Core
)

add_subdirectory(src)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
