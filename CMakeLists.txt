cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang)
set(CMAKE_INSTALL_PREFIX /usr/local)

project(logsquid)
set(PROJECT_LABEL logSquid)

if (${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")
    include_directories(/usr/local/include)
    link_directories(/usr/local/lib /usr/local/lib/mysql)
endif()

file(GLOB LIB_HEADERS_SERVER src/lib/lmysql.h src/lib/services.h)
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


file(GLOB CONF_FILES conf/${PROJECT_NAME}_agent.conf conf/${PROJECT_NAME}_server.conf)

install(TARGETS ${PROJECT_NAME}_agent ${PROJECT_NAME}_server DESTINATION bin)
install(FILES ${CONF_FILES} DESTINATION etc/${PROJECT_LABEL})
install(DIRECTORY DESTINATION /var/log/${PROJECT_LABEL})
