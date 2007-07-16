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

static inline char *skipminus(char *s)
{
	while (*s == '-')
		s++;
	return s;
}

static inline char *paramornull(char *s)
{
	if (*s == '-')
		return NULL;
	return s;
}

static inline char get_shortopt(char *rawarg)
{
	if (rawarg[0] && rawarg[0] == '-'
			&& rawarg[1] && rawarg[1] != '-'
			&& !rawarg[2])
		return rawarg[1];
	return 0;
}

struct copme_long *copme_option_named(struct copme_long *opts, char *lname)
{
	for (struct copme_long *o = opts; o->lname; o++)
		if (strcmp(o->lname, lname) == 0)
			return o;
	return NULL;
}

void copme_usage(struct copme_state *st, void (*pre)(void), void (*post)(void))
{
	static const int desc = 25;

	if (pre)
		pre();

	printf("Options:\n");
	for (struct copme_long *o = st->opts; o->lname; o++) {
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
		printf("%s\n", o->desc);
	}

	if (post)
		post();
}

struct copme_state *
copme_init(struct copme_long *opts, int argc, char *argv[])
{
	struct copme_state *st = malloc(sizeof(*st));

	st->opts = opts;
	st->argc = argc;
	st->argv = argv;
	st->argind = 0;

	for (struct copme_long *o = st->opts; o->lname; o++) {
		o->specified = 0;
		if (o->arg) {
			o->arg->specified = 0;
			o->arg->data = NULL;
		}
	}

	return st;
}

void copme_next(struct copme_state *state)
{
	if (copme_finished(state) || copme_error(state))
		return;

	state->argind++;
	state->curopt = -1;
	state->curarg = NULL;

	if (copme_finished(state))
		return;

	char *rawarg = state->argv[state->argind];
	char *curarg = skipminus(rawarg);
	char shortopt = get_shortopt(rawarg);

	for (struct copme_long *o = state->opts; o->lname; o++) {
		if (strcmp(o->lname, curarg) != 0
				&& (shortopt == 0 || shortopt != o->sname))
			continue;

		o->specified++;
		state->curopt = o - state->opts;

		if (o->arg_kind == COPME_NOARG)
			state->curarg = NULL;
		else if (o->arg_kind == COPME_HASARG) {
			state->argind++;
			if (state->argind >= state->argc
					|| state->argv[state->argind][0] == '-') {
				fprintf(stderr, "Option '%s' needs an argument.\n", curarg);
				goto err;
			}
			state->curarg = state->argv[state->argind];
		} else if (o->arg_kind == COPME_OPTARG) {
			state->argind++;
			if (state->argind < state->argc)
				state->curarg = paramornull(state->argv[state->argind]);
			if (state->curarg == NULL)
				state->argind--;
		}

		if (o->arg != NULL) {
			o->arg->specified = (state->curarg != NULL);
			o->arg->data = state->curarg;
		}

		return;
	}

	fprintf(stderr, "Unkown option '%s'\n", curarg);
err:
	state->error = 1;
}
