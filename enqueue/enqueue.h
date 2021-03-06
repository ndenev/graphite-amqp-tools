/*
 * Copyright (c) 2012 Matt Dainty <matt@bodgit-n-scarper.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _ENQUEUE_H
#define _ENQUEUE_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/queue.h>

#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>

#include "common.h"

#define	ENQUEUE_CONF_FILE	"/usr/local/etc/graphite-enqueue.conf"
#define	ENQUEUE_USER		"_enqueue"

struct listen_addr {
	TAILQ_ENTRY(listen_addr)	 entry;
	struct sockaddr_storage		 sa;
	int				 fd;
	struct event			*ev;
	int				 port;
};

struct enqueue_addr {
	struct enqueue_addr	*next;
	struct sockaddr_storage	 ss;
};

struct enqueue_addr_wrap {
	char			*name;
	struct enqueue_addr	*a;
};

struct enqueue {
	struct event_base			*base;

	TAILQ_HEAD(listen_addrs, listen_addr)	 listen_addrs;

	struct amqp				*amqp;

	char					*buffer;
	struct event				*ev;
	struct timeval				 t;
};

/* prototypes */
/* parse.y */
struct enqueue	*parse_config(const char *, int);
int		 host(const char *, struct enqueue_addr **);
int		 host_dns(const char *, struct enqueue_addr **);

#endif
