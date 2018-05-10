cmake_minimum_required(VERSION 2.8)

SET (CMAKE_C_COMPILER /usr/bin/clang)
SET (CMAKE_CXX_COMPILER /usr/bin/clang)

project(logsquid)

if (${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")
    include_directories(/usr/local/include)
endif()

file(GLOB LIB_HEADERS_SERVER src/lib/lmysql.c src/lib/services.h)
file(GLOB LIB_SOURCES_SERVER src/lib/lmysql.c src/lib/services.c)

file(GLOB LIB_HEADERS src/lib/config.h src/lib/daemon.h src/lib/debug.h src/lib/log.h)
file(GLOB LIB_SOURCES src/lib/config.c src/lib/daemon.c src/lib/debug.c src/lib/log.c)

file(GLOB SOURCES_SERVER src/${PROJECT_NAME}_server/*.c)
file(GLOB HEADERS_SERVER src/${PROJECT_NAME}_server/*.h)
add_executable(${PROJECT_NAME}_server ${SOURCES_SERVER} ${HEADERS_SERVER} ${LIB_SOURCES} ${LIB_HEADERS} ${LIB_SOURCES_SERVER} ${LIB_HEADERS_SERVER})
target_link_libraries(${PROJECT_NAME}_server pthread mysqlclient gcrypt gpg-error confuse)

file(GLOB SOURCES_AGENT src/${PROJECT_NAME}_agent/*.c)
file(GLOB HEADERS_AGENT src/${PROJECT_NAME}_agent/*.h)
add_executable(${PROJECT_NAME}_agent ${SOURCES_AGENT} ${HEADERS_AGENT} ${LIB_SOURCES} ${LIB_HEADERS})
target_link_libraries(${PROJECT_NAME}_agent pthread confuse m)
