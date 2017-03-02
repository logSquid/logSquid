EXTRA_DIST = \
	www

FRONTEND_CONFIG = logsquid_apache.conf
PATH_LGSQD = logSquid
SHARE_DIR = $(DESTDIR)/usr/share/logSquid/frontend/

install-data-hook:
	$(MKDIR_P) "$(SHARE_DIR)"
	cp -r "www" "$(SHARE_DIR)"
	cp "../../misc/license/license" "$(SHARE_DIR)"
	cp "../../conf/$(FRONTEND_CONFIG)" "$(SHARE_DIR)$(FRONTEND_CONFIG)"

