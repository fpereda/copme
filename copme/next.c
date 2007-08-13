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

static inline char *paramornull(char *s)
{
	if (s == NULL || *s == '-')
		return NULL;
	return s;
}

void copme_next(struct copme_state *state)
{
	if (copme_finished(state) || copme_error(state))
		return;

	state->argind++;
	state->curopt = NULL;

	if (copme_finished(state))
		return;

	char *rawarg = state->argv[state->argind];
	char *curarg = NULL;
	char *multishort = NULL;
	char shortopt = 0;
	size_t lenraw = strlen(rawarg);

	if (lenraw == 2 && rawarg[0] == '-' && rawarg[1] != '-')
		shortopt = rawarg[1];
	else if (lenraw > 2 && rawarg[0] == '-' && rawarg[1] == '-')
		curarg = rawarg + 2;
	else if (lenraw > 2 && rawarg[0] == '-' && rawarg[1] != '-')
		multishort = rawarg + 1;

	/* This is neither a short nor a long nor a multishort option. */
	if (!curarg && shortopt == 0 && !multishort) {
		struct copme_nopts *nopts = &state->nopts;
		if (nopts->count >= nopts->size) {
			nopts->size *= COPME_NOPTV_GROWTH_RATE;
			nopts->noptv = xrealloc(nopts->noptv, nopts->size);
		}
		nopts->noptv[nopts->count++] = rawarg;
		return;
	}

	char *equal = NULL;
	if (curarg)
		equal = strchr(curarg, '=');

	int lencmp = equal ? equal - curarg : lenraw - 2;

	char *nextarg = NULL;
	if (multishort)
		nextarg = NULL;
	else if (equal)
		nextarg = equal + 1;
	else
		nextarg = paramornull(state->argv[state->argind + 1]);

	copme_foreach_group_option(state, g, o) {
		if (curarg && strncmp(o->lname, curarg, lencmp) != 0)
			continue;
		if (shortopt && shortopt != o->sname)
			continue;
		if (multishort && *multishort != o->sname)
			continue;

		o->specified++;
		state->curopt = o;

		char *arg_data = NULL;

		if (o->arg_kind == COPME_NOARG)
			arg_data = NULL;
		else if (o->arg_kind == COPME_OPTARG && nextarg)
			arg_data = nextarg;
		else if (o->arg_kind == COPME_HASARG) {
			if (!nextarg)
				goto needarg;
			arg_data = nextarg;
		}

		if ((o->arg_kind == COPME_HASARG || o->arg_kind == COPME_OPTARG)
				&& nextarg && ! equal)
			state->argind++;

		if (o->arg) {
			o->arg->specified = (arg_data != NULL);
			o->arg->data = arg_data;
		}

		if (multishort && *(++multishort))
			/* 'o++' will give us g->opts when we enter the loop. */
			o = g->opts - 1;
		else
			return;
	}

	if (curarg)
		fprintf(stderr, "Unknown long option '%s'\n", curarg);
	else if (multishort)
		fprintf(stderr,
				"Unknown short option '%c'(%d). Part of multishort.\n",
				*multishort, *multishort);
	else
		fprintf(stderr, "Unknown short option '%c'\n", shortopt);
	goto err;
needarg:
	if (curarg)
		fprintf(stderr, "Option '%s' needs an argument.\n", curarg);
	else
		fprintf(stderr, "Option '%c' needs an argument.\n", shortopt);
	goto err;
err:
	state->error = 1;
}
