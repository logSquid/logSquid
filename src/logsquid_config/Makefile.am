AUTOMAKE_OPTIONS = foreign subdir-objects

bin_PROGRAMS = logsquid_config
logsquid_configdir = $(includedir)

logsquid_config_SOURCES = ../lib/config.c ../lib/config.h\
		../lib/log.c ../lib/log.h\
		../lib/debug.c ../lib/debug.h\
		../lib/daemon.c ../lib/daemon.h\
		../lib/lmysql.c ../lib/lmysql.h\
		../lib/services.c ../lib/services.h\
		logsquid_config.c

#logsquid_server_HEADERS = ../lib/config.c ../lib/config.h ../lib/log.c ../lib/log.h ../lib/debug.c ../lib/debug.h readlog.c readlog.h
#-lmysqlclient

CFLAGS = -W -Wall
LDFLAGS=-L/usr/local/lib -L/usr/local/lib/mysql
LIBS = -lconfuse -lm -lmysqlclient -lgcrypt

PATH_LGSQD = logSquid
SHARE_DIR = $(DESTDIR)/usr/share/logSquid/config/
DB_DIR = $(SHARE_DIR)database/

install-data-hook:
	$(MKDIR_P) "$(DB_DIR)"
	cp "../../misc/database/logSquid.sql" "$(DB_DIR)logSquid.sql"
	cp "../../misc/database/users.sql" "$(DB_DIR)users.sql"
	cp "../../misc/database/servers.sql" "$(DB_DIR)servers.sql"
	cp "../../misc/database/agents.sql" "$(DB_DIR)agents.sql"
