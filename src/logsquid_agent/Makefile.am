AUTOMAKE_OPTIONS = foreign subdir-objects

bin_PROGRAMS = logsquid_agent
logsquid_agentdir = $(includedir)

logsquid_agent_SOURCES = ../lib/config.c ../lib/config.h\
		../lib/log.c ../lib/log.h\
		../lib/debug.c ../lib/debug.h\
		../lib/daemon.c ../lib/daemon.h\
		agent.c agent.h\
		readlog.c readlog.h\
		logsquid_agent.c

#logsquid_agent_HEADERS = ../lib/config.c ../lib/config.h ../lib/log.c ../lib/log.h ../lib/debug.c ../lib/debug.h readlog.c readlog.h

CFLAGS = -W -Wall
LDFLAGS=-L/usr/local/lib
LIBS = -lconfuse -lm -lpthread

AGENT_CONFIG = logsquid_agent.conf
PATH_LGSQD = logSquid
SHARE_DIR = $(DESTDIR)/usr/share/logSquid/agent/

install-data-hook:
	$(MKDIR_P) "/var/log/logSquid/agent/"
	$(MKDIR_P) "$(SHARE_DIR)"
	cp "../../conf/$(AGENT_CONFIG)" "$(SHARE_DIR)logsquid_agent.conf"
	$(MKDIR_P) "$(SHARE_DIR)debian/"
	$(MKDIR_P) "$(SHARE_DIR)rdht/"
	$(MKDIR_P) "$(SHARE_DIR)freebsd/"
	$(MKDIR_P) "$(SHARE_DIR)systemd/"
	cp "../../misc/license/license" "$(SHARE_DIR)"
	cp "../../misc/init.d/debian/logsquid_agent" "$(SHARE_DIR)debian/logsquid_agent"
	cp "../../misc/init.d/rdht/logsquid_agent" "$(SHARE_DIR)rdht/logsquid_agent"
	cp "../../misc/init.d/freebsd/logsquid_agent" "$(SHARE_DIR)freebsd/logsquid_agent"
	cp "../../misc/systemd/logsquid_agent.service" "$(SHARE_DIR)systemd/logsquid_agent.service"
