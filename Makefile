# vt_lock - simple vt lock utility
# © 2019 lomonosow

NAME = vt_lock
VERSION = 0.1

CC := $(CC) -std=c99

base_CFLAGS = -Wall -Wextra -pedantic -O2 -g


CPPFLAGS += -DPROGNAME=\"${NAME}\" -DVERSION=\"${VERSION}\" -D_XOPEN_SOURCE=500
CFLAGS := $(base_CFLAGS) $(CFLAGS)
LDLIBS := $(base_LIBS)

all: vt_lock

vt_lock: vt_lock.c

clean:
	$(RM) vt_lock

install: vt_lock
	install -Dm4755 vt_lock $(DESTDIR)/usr/bin/vt_lock
