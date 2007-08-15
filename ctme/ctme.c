/* vim: set sts=4 sw=4 noet : */

/*
 * Copyright (c) 2006, Fernando J. Pereda <ferdy@gentoo.org>
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

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>

#include "ctme.h"

void CTME_ERR(const char *fmt, ...)
{
	va_list list;

	va_start(list, fmt);
	vfprintf(stderr, fmt, list);
	va_end(list);

	ctme_err = 1;
	ctme_ntests++;
}

static void do_run_test(const char *tit)
{
	struct timeval tv_pre;
	struct timeval tv_post;
	ctme_err = 0;
	ctme_ntests = 0;
	printf("%s: ", tit);
	gettimeofday(&tv_pre, NULL);
	run_test();
	gettimeofday(&tv_post, NULL);
	const unsigned long ms =
		((tv_post.tv_sec - tv_pre.tv_sec) * 1000) +
		((tv_post.tv_usec - tv_pre.tv_usec) / 1000);
	printf("%sOK (%ldms)\n", ctme_err ? " NOT " : " ", ms);
}

int main(int argc, char *argv[])
{
	setbuf(stdout, 0);

	do_run_test(name());

	if (!ctme_err && repeat())
		do_run_test("(repeat)");

	return ctme_err;
}
