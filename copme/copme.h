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

#ifndef COPME_GUARD_COPME_H
#define COPME_GUARD_COPME_H 1

#if defined(__GNUC__)
#    define COPME_ATTRIBUTE(x) __attribute__((x))
#else
#    define COPME_ATTRIBUTE(x)
#endif

#define copme_foreach_group(s, g) \
	for (struct copme_group *g = (s)->groups; g->sdesc; g++)

#define copme_foreach_option(g, o) \
	for (struct copme_long *o = (g)->opts; o->lname; o++)

#define copme_foreach_group_option(s, g, o) \
	copme_foreach_group(s, g) \
		copme_foreach_option(g, o)

struct copme_arg {
	char *data;
	unsigned specified : 1;
};

struct copme_long {
	char *lname;
	char sname;
	char *desc;
	enum copme_arg_kind {
		COPME_NOARG,
		COPME_HASARG,
		COPME_OPTARG
	} arg_kind;
	struct copme_arg *arg;
	unsigned specified;
};

struct copme_group {
	char *sdesc;
	char *ldesc;
	struct copme_long *opts;
};

struct copme_state {
	unsigned argind;
	int argc;
	char **argv;
	struct copme_group *groups;
	char *curarg;
	struct copme_long *curopt;
	unsigned finished : 1;
	unsigned error    : 1;
};

struct copme_long *
copme_option_named(struct copme_group *groups, char *lname);

struct copme_state *
copme_init(struct copme_group groups[], int argc, char *argv[]);

void copme_next(struct copme_state *st);
void copme_usage(struct copme_state *st,
		void (*pre)(void), void (*post)(void));

static inline unsigned copme_finished(struct copme_state *st)
{
	return st->finished || st->argind >= st->argc;
}

static inline unsigned copme_error(struct copme_state *st)
{
	return st->error;
}

static inline struct copme_long *copme_current_opt(struct copme_state *st)
{
	return st->curopt;
}

static inline char *copme_arg(struct copme_state *st)
{
	return st->curarg;
}

#endif
