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

#include <ctme/ctme.h>

#include <copme/copme.h>

char *name(void)
{
	static char n[] = "basic opt handling";
	return n;
}

int repeat(void)
{
	return 1;
}

void run_test(void)
{
	struct copme_arg a_depth;
	struct copme_arg a_axiom;
	struct copme_arg a_multi;
	struct copme_arg a_optional;

	struct copme_long opts[] = {
		{"depth", 'd', "Depth of the L-System", COPME_HASARG, &a_depth},
		{"axiom", 'a', "Axiom of the L-System", COPME_HASARG, &a_axiom},
		{"multi", 'm', "Specify multiple times", COPME_HASARG, &a_multi},
		{"optional", 'o', "Optional argument", COPME_OPTARG, &a_optional},
		{"help" , 'h', "Display this help information", COPME_NOARG, 0},
		{0, 0, 0, 0, 0}
	};

	struct copme_long *o_help = copme_option_named(opts, "help");
	struct copme_long *o_multi = copme_option_named(opts, "multi");
	struct copme_long *o_optional = copme_option_named(opts, "optional");

	CTME_CHECK_NOT_NULL(o_help);
	CTME_CHECK_NOT_NULL(o_multi);
	CTME_CHECK_NOT_NULL(o_optional);

	struct copme_long *o_nothing = copme_option_named(opts, "idonotexist");

	CTME_CHECK_NULL(o_nothing);

	int targc = 1;
	char *targv[] = {
		"something",
		NULL
	};
	struct copme_state *st = copme_init(opts, targc, targv);

	CTME_CHECK_NOT_NULL(st);

	struct copme_long *o;
	for (o = opts; o->lname; o++) {
		CTME_CHECK_EQUAL(o->specified, 0);
		if (o->arg) {
			CTME_CHECK_EQUAL(o->arg->specified, 0);
			CTME_CHECK_NULL(o->arg->data);
		}
	}

	free(st);
}
