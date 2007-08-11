/* vim: set sts=4 sw=4 noet : */

/*
 * Copyright (c) 2007, Fernando J. Pereda <ferdy@gentoo.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the library nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "copme.h"
#include "xfuncs.h"

void copme_free(struct copme_state *st)
{
	copme_foreach_group_option(st, g, o) {
		if (o->arg)
			free(o->arg);
	}
	free(st);
}

struct copme_state *
copme_init(struct copme_group *groups, int argc, char *argv[])
{
	struct copme_state *st = xmalloc(sizeof(*st));

	st->groups = groups;
	st->argc = argc;
	st->argv = argv;
	st->curopt = NULL;
	st->curarg = NULL;
	st->argind = 0;
	st->error = 0;
	st->finished = 0;

	copme_foreach_group_option(st, g, o) {
		o->specified = 0;
		if (o->arg_kind == COPME_NOARG)
			continue;
		o->arg = xmalloc(sizeof(*o->arg));
		o->arg->specified = 0;
		o->arg->data = NULL;
	}

	return st;
}

struct copme_long *copme_option_named(struct copme_group *groups, char *lname)
{
	for (struct copme_group *g = groups; g->sdesc; g++)
		copme_foreach_option(g, o)
			if (strcmp(o->lname, lname) == 0)
				return o;
	return NULL;
}

void copme_usage(struct copme_state *st, void (*pre)(void), void (*post)(void))
{
	static const unsigned desc = 25;

	if (pre)
		pre();

	copme_foreach_group(st, g) {
		printf("%s:\n", g->sdesc);
		copme_foreach_option(g, o) {
			unsigned totlen = 0;
			totlen += 4;
			totlen += strlen(o->lname);
			if (o->sname != 0)
				totlen += 4;
			printf("  --%s", o->lname);
			if (o->sname != 0)
				printf(", -%c", o->sname);
			unsigned n = desc - totlen;
			if (totlen >= desc) {
				n = desc;
				putchar('\n');
			}
			while (n--)
				putchar(' ');
			printf("%s\n", o->desc ? o->desc : "No help available.");
		}
		putchar('\n');
	}

	if (post)
		post();
}
