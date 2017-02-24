CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
PROJECT(TimeToWork)

SET(CMAKE_CXX_STANDARD 14)


FIND_PACKAGE(Qt5 REQUIRED COMPONENTS Core Quick Concurrent)

# Instruct CMake to run moc automatically when needed.
SET(CMAKE_AUTOMOC ON)

QT5_ADD_RESOURCES(RESOURCES res/qml.qrc)

LIST(APPEND QML_DIRS ${PROJECT_SOURCE_DIR}/res/view)
SET(QML_IMPORT_PATH "${QML_DIRS}" CACHE STRING "Qt Creator extra qml import paths" FORCE)

SET(QML_SRC
		res/view/main.qml
		res/view/component/Space.qml
		)

SET(SOURCE_FILES
		src/AppController.cpp src/AppController.h
		src/plugin/redmine/api/data/Error.h
		src/plugin/redmine/api/data/Issue.h
		src/plugin/redmine/api/data/Project.h
		src/plugin/redmine/api/data/TimeEntry.h
		src/plugin/redmine/api/data/User.h
		src/plugin/redmine/api/data/WorkActivity.h
		src/plugin/redmine/api/Enumerations.cpp src/plugin/redmine/api/Enumerations.h
		src/plugin/redmine/api/TimeEntries.cpp src/plugin/redmine/api/TimeEntries.h
		src/plugin/redmine/RedmineApi.cpp src/plugin/redmine/RedmineApi.h
		)

ADD_EXECUTABLE(TimeToWork main.cpp ${SOURCE_FILES} ${RESOURCES})

# Add QML files to project tree without building/compiling them
ADD_CUSTOM_TARGET(myApp SOURCES ${QML_SRC})

TARGET_COMPILE_OPTIONS(TimeToWork PRIVATE
		-Wall -pedantic -Werror
		-Wno-unused-private-field -Wnon-virtual-dtor)

TARGET_INCLUDE_DIRECTORIES(TimeToWork PRIVATE
		./src
		${CMAKE_CURRENT_BINARY_DIR}
		./
		)

TARGET_LINK_LIBRARIES(TimeToWork Qt5::Core Qt5::Quick Qt5::Concurrent)

SET(POCO_STATIC ON CACHE BOOL "" FORCE)

ADD_DEFINITIONS(-DPOCO_SOCKETADDRESS_DONT_PREFER_IPV4)
ADD_SUBDIRECTORY(lib/poco)

TARGET_LINK_LIBRARIES(TimeToWork PocoNet PocoNetSSL PocoUtil PocoData PocoDataSQLite PocoJSON)
