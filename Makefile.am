if SERVER
SERVER_SUBDIRS=src/logsquid_server
CONFIG_SUBDIRS=src/logsquid_config
EXTRA_DIST = conf/logsquid_server.conf
endif

if AGENT
AGENT_SUBDIRS=src/logsquid_agent
EXTRA_DIST = conf/logsquid_agent.conf
endif

if FRONTEND
FRONTEND_SUBDIRS=src/logsquid_frontend
EXTRA_DIST = conf/logsquid_apache.conf
endif

Projetodir = $(prefix)

SUBDIRS = $(SERVER_SUBDIRS) \
	$(CONFIG_SUBDIRS) \
	$(AGENT_SUBDIRS) \
	$(FRONTEND_SUBDIRS) \
	misc \
	conf
