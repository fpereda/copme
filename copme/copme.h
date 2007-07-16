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

#ifndef __COPME_H
#define __COPME_H 1

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

struct copme_state {
	unsigned argind;
	int argc;
	char **argv;
	struct copme_long *opts;
	char *curarg;
	unsigned curopt;
	unsigned finished : 1;
	unsigned error    : 1;
};

struct copme_long *
copme_option_named(struct copme_long *opts, char *lname);

struct copme_state *
copme_init(struct copme_long opts[], int argc, char *argv[]);

void copme_next(struct copme_state *st);
void copme_usage(struct copme_state *st);

static inline unsigned copme_finished(struct copme_state *st)
{
	return st->finished || st->argind >= st->argc;
}

static inline unsigned copme_error(struct copme_state *st)
{
	return st->error;
}

static inline char *copme_current_long(struct copme_state *st)
{
	return st->opts[st->curopt].lname;
}

static inline char copme_current_short(struct copme_state *st)
{
	return st->opts[st->curopt].sname;
}

static inline unsigned copme_current_opt(struct copme_state *st)
{
	return st->curopt;
}

static inline char *copme_arg(struct copme_state *st)
{
	return st->curarg;
}

#endif
