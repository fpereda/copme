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

#define SIZEOF_ARRAY(a) (sizeof(a)/sizeof(a[0]))

char *name(void)
{
	static char n[] = "COPME_OPTARG handling";
	return n;
}

int repeat(void)
{
	return 1;
}

void run_test(void)
{
	struct copme_long opts[] = {
		{"one", 'o', "First opt", COPME_NOARG},
		{"two", 't', "Second opt", COPME_HASARG},
		{"three", 'r', "Third opt", COPME_OPTARG},
		{0, 0, 0, 0, 0}
	};

	struct copme_group groups[] = {
		{"Options", "Options for blabla", opts},
		{0, 0, 0}
	};

	struct copme_long *o_one = copme_option_named(groups, "one");
	struct copme_long *o_two = copme_option_named(groups, "two");
	struct copme_long *o_three = copme_option_named(groups, "three");

	CTME_CHECK_NOT_NULL(o_one);
	CTME_CHECK_NOT_NULL(o_two);

	char *targv[] = {
		"program",
		"-r",
		"--two",
		"something",
		NULL
	};
	int targc = SIZEOF_ARRAY(targv) - 1;

	struct copme_state *st = copme_init(groups, targc, targv);

	CTME_CHECK_NOT_NULL(st);

	while (! copme_finished(st) && ! copme_error(st))
		copme_next(st);

	CTME_CHECK(! copme_error(st));
	CTME_CHECK(copme_finished(st));
	CTME_CHECK(! o_one->specified);
	CTME_CHECK(o_two->specified);
	CTME_CHECK(o_two->arg->specified);
	CTME_CHECK_EQUAL_STRING(o_two->arg->data, "something");
	CTME_CHECK(o_three->specified);
	CTME_CHECK(! o_three->arg->specified);

	copme_free(st);

	char *targv2[] = {
		"program",
		"--two=one",
		"--three=blah",
		NULL
	};
	int targc2 = SIZEOF_ARRAY(targv2) - 1;

	st = copme_init(groups, targc2, targv2);

	CTME_CHECK(! o_two->specified);
	CTME_CHECK_NOT_NULL(st);

	while (! copme_finished(st) && ! copme_error(st))
		copme_next(st);

	CTME_CHECK(! copme_error(st));
	CTME_CHECK(copme_finished(st));
	CTME_CHECK(! o_one->specified);
	CTME_CHECK(o_two->specified == 1);
	CTME_CHECK(o_two->arg->specified);
	CTME_CHECK_EQUAL_STRING(o_two->arg->data, "one");
	CTME_CHECK(o_three->specified);
	CTME_CHECK(o_three->arg->specified);
	CTME_CHECK_EQUAL_STRING(o_three->arg->data, "blah");

	copme_free(st);

	char *targv3[] = {
		"program",
		"--one",
		"--two=one",
		"-t",
		"two",
		"-r",
		"gulp",
		NULL
	};
	int targc3 = SIZEOF_ARRAY(targv3) - 1;

	st = copme_init(groups, targc3, targv3);

	CTME_CHECK(! o_two->specified);
	CTME_CHECK_NOT_NULL(st);

	while (! copme_finished(st) && ! copme_error(st))
		copme_next(st);

	CTME_CHECK(! copme_error(st));
	CTME_CHECK(copme_finished(st));
	CTME_CHECK(o_one->specified);
	CTME_CHECK(o_two->specified == 2);
	CTME_CHECK(o_two->arg->specified);
	CTME_CHECK_EQUAL_STRING(o_two->arg->data, "two");
	CTME_CHECK(o_three->specified);
	CTME_CHECK(o_three->arg->specified);
	CTME_CHECK_EQUAL_STRING(o_three->arg->data, "gulp");
	CTME_CHECK(copme_nopts(st)->count == 0);

	copme_free(st);

	char *targv4[] = {
		"program",
		"--one",
		"--two=one",
		"-t",
		"two",
		"-r",
		"gulp",
		"--three",
		NULL
	};
	int targc4 = SIZEOF_ARRAY(targv4) - 1;

	st = copme_init(groups, targc4, targv4);

	CTME_CHECK(! o_two->specified);
	CTME_CHECK_NOT_NULL(st);

	while (! copme_finished(st) && ! copme_error(st))
		copme_next(st);

	CTME_CHECK(! copme_error(st));
	CTME_CHECK(copme_finished(st));
	CTME_CHECK(o_one->specified);
	CTME_CHECK(o_two->specified == 2);
	CTME_CHECK(o_two->arg->specified);
	CTME_CHECK_EQUAL_STRING(o_two->arg->data, "two");
	CTME_CHECK(o_three->specified == 2);
	CTME_CHECK(! o_three->arg->specified);
	CTME_CHECK_NULL(o_three->arg->data);
	CTME_CHECK(copme_nopts(st)->count == 0);

	copme_free(st);
}
