#                                               -*- Autoconf -*-
AC_PREREQ([2.69])
AC_INIT(logSquid, 2.0, mauro@vantageti.com.br, logsquid, http://logsquid.com/)

AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC

# Checks for header files.
AC_CHECK_HEADERS([stdio.h stdlib.h confuse.h getopt.h unistd.h unistd.h stat.h errno.h dirent.h time.h fcntl.h malloc.h sys/socket.h sys/types resolv.h netdb.h netinet/in.h netinet/ip.h arpa/inet.h pthread.h mysql/mysql.h sys/uio.h])
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([strerror])

AC_ARG_ENABLE(server, [ --enable-server		Turn on build of logSquid Server ],
[case "${enableval}" in 
	yes) 
		AC_CONFIG_FILES([src/logsquid_server/Makefile src/logsquid_config/Makefile])
		AC_DEFINE([CONF_FILE], ["conf/logsquid_server.conf"], [Settings Files])
		server=yes ;;
  	*) 
		AC_MSG_ERROR([bad value ${enableval} for --enable-server]) ;;
	esac],
[server=no])
AM_CONDITIONAL(SERVER, test "x$server" = "xyes")

AC_ARG_ENABLE(agent, [ --enable-agent		Turn on build of logSquid Agent ],
[case "${enableval}" in 
	yes) 
		AC_CONFIG_FILES([src/logsquid_agent/Makefile]) 
		AC_DEFINE([CONF_FILE], ["conf/logsquid_agent.conf"], [Settings Files])
		agent=yes ;;
  	*) 
		AC_MSG_ERROR([bad value ${enableval} for --enable-agent]) ;;
	esac],
[agent=no])
AM_CONDITIONAL(AGENT, test "x$agent" = "xyes")

AC_ARG_ENABLE(frontend, [ --enable-frontend	Turn on build of logSquid Frontend ],
[case "${enableval}" in 
	yes) 
		AC_CONFIG_FILES([src/logsquid_frontend/Makefile]) 
		AC_DEFINE([CONF_FILE], ["conf/logsquid_apache.conf"], [Settings Files])
		frontend=yes ;;
  	*) 
		AC_MSG_ERROR([bad value ${enableval} for --enable-frontend]) ;;
	esac],
[frontend=no])
AM_CONDITIONAL(FRONTEND, test "x$frontend" = "xyes")

AC_CONFIG_FILES([Makefile misc/Makefile conf/Makefile])

AC_OUTPUT
