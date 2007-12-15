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
	struct copme_long opts[] = {
		{"depth", 'd', "Depth of the L-System", COPME_HASARG},
		{"axiom", 'a', "Axiom of the L-System", COPME_HASARG},
		{"multi", 'm', "Specify multiple times", COPME_HASARG},
		{"optional", 'o', "Optional argument", COPME_OPTARG},
		{"help" , 'h', "Display this help information", COPME_NOARG},
		{0, 0, 0, 0, 0}
	};

	struct copme_group groups[] = {
		{"Options", "Some options blabla", opts},
		{0, 0, 0}
	};

	struct copme_long *o_help = copme_option_named(groups, "help");
	struct copme_long *o_multi = copme_option_named(groups, "multi");
	struct copme_long *o_optional = copme_option_named(groups, "optional");

	CTME_CHECK_NOT_NULL(o_help);
	CTME_CHECK_NOT_NULL(o_multi);
	CTME_CHECK_NOT_NULL(o_optional);

	struct copme_long *o_nothing = copme_option_named(groups, "idonotexist");

	CTME_CHECK_NULL(o_nothing);

	int targc = 1;
	char *targv[] = {
		"something",
		NULL
	};

	struct copme_state *st = copme_init(groups, targc, targv);

	CTME_CHECK_NOT_NULL(st);

	copme_foreach_option(groups, o) {
		CTME_CHECK_EQUAL(o->specified, 0);
		if (o->arg_kind == COPME_NOARG)
			continue;
		CTME_CHECK_EQUAL(o->arg->specified, 0);
		CTME_CHECK_NULL(o->arg->data);
	}

	CTME_CHECK_EQUAL(copme_extra(st), 1);
	CTME_CHECK_NULL(targv[copme_extra(st)]);

	copme_free(st);

	int targc2 = 6;
	char *targv2[] = {
		"something",
		"--optional",
		"-a",
		"bleh",
		"--",
		"foo",
		NULL
	};

	st = copme_init(groups, targc2, targv2);

	CTME_CHECK_NOT_NULL(st);

	while (! copme_finished(st))
		copme_next(st);

	CTME_CHECK_EQUAL(copme_extra(st), 5);
	CTME_CHECK_EQUAL_STRING(targv2[copme_extra(st)], "foo");

	copme_free(st);

	int targc3 = 2;
	char *targv3[] = {
		"something",
		"--",
		NULL
	};

	st = copme_init(groups, targc3, targv3);

	CTME_CHECK_NOT_NULL(st);

	while (! copme_finished(st))
		copme_next(st);

	CTME_CHECK_EQUAL(copme_extra(st), 2);
	CTME_CHECK_NULL(targv3[copme_extra(st)]);

	copme_free(st);

	int targc4 = 5;
	char *targv4[] = {
		"something",
		"--optional",
		"-a",
		"bleh",
		"foo",
		NULL
	};

	st = copme_init(groups, targc4, targv4);

	CTME_CHECK_NOT_NULL(st);

	while (! copme_finished(st))
		copme_next(st);

	CTME_CHECK_EQUAL(copme_extra(st), 5);
	CTME_CHECK_NULL(targv4[copme_extra(st)]);

	copme_free(st);
}
