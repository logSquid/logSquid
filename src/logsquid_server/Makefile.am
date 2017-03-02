AUTOMAKE_OPTIONS = foreign subdir-objects

bin_PROGRAMS = logsquid_server
logsquid_serverdir = $(includedir)

logsquid_server_SOURCES = ../lib/config.c ../lib/config.h\
		../lib/log.c ../lib/log.h\
		../lib/debug.c ../lib/debug.h\
		../lib/daemon.c ../lib/daemon.h\
		../lib/lmysql.c ../lib/lmysql.h\
		../lib/services.c ../lib/services.h\
		server.c server.h\
		logsquid_server.c

#logsquid_server_HEADERS = ../lib/config.c ../lib/config.h ../lib/log.c ../lib/log.h ../lib/debug.c ../lib/debug.h readlog.c readlog.h
#-lmysqlclient

CFLAGS = -W -Wall
LDFLAGS=-L/usr/local/lib -L/usr/local/lib/mysql
LIBS = -lconfuse -lm -lpthread -lmysqlclient -lgcrypt

SERVER_CONFIG = logsquid_server.conf
PATH_LGSQD = logSquid
SHARE_DIR = $(DESTDIR)/usr/share/logSquid/server/

install-data-hook:
	$(MKDIR_P) "/var/log/logSquid/server/"
	$(MKDIR_P) "$(SHARE_DIR)"
	cp "../../conf/$(SERVER_CONFIG)" "$(SHARE_DIR)logsquid_server.conf"
	$(MKDIR_P) "$(SHARE_DIR)debian/"
	$(MKDIR_P) "$(SHARE_DIR)rdht/"
	$(MKDIR_P) "$(SHARE_DIR)freebsd/"
	$(MKDIR_P) "$(SHARE_DIR)systemd/"
	cp "../../misc/license/license" "$(SHARE_DIR)"
	cp "../../misc/init.d/debian/logsquid_server" "$(SHARE_DIR)debian/logsquid_server"
	cp "../../misc/init.d/rdht/logsquid_server" "$(SHARE_DIR)rdht/logsquid_server"
	cp "../../misc/init.d/freebsd/logsquid_server" "$(SHARE_DIR)freebsd/logsquid_server"
	cp "../../misc/systemd/logsquid_server.service" "$(SHARE_DIR)systemd/logsquid_server.service"
