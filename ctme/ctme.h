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

#ifndef CTME_GUARD_CTME_H
#define CTME_GUARD_CTME_H 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int ctme_err;
unsigned int ctme_ntests;

#define CTME_PASS() putchar('.')

#define CTME_CHECK(c) do { \
	if (!(c)) { \
		fprintf(stderr, "\n Assertion '"#c"' failed\n"); \
		ctme_err = 1; \
	} else \
		CTME_PASS(); \
	ctme_ntests++; \
} while (0)

#define CTME_CHECK_EQUAL(a, b) CTME_CHECK(a == b)
#define CTME_CHECK_NOT_EQUAL(a, b) CTME_CHECK(a != b)
#define CTME_CHECK_NULL(a) CTME_CHECK((a) == NULL)
#define CTME_CHECK_NOT_NULL(a) CTME_CHECK((a) != NULL)

#define CTME_CHECK_EQUAL_STRING(a, b) do { \
	if (strcmp((a), (b)) != 0) { \
		fprintf(stderr, "\n Expected '%s' but got '%s'\n", (b), (a)); \
		ctme_err = 1; \
	} else \
		CTME_PASS(); \
	ctme_ntests++; \
} while (0)

void CTME_ERR(const char *fmt, ...);

extern char *name(void);
extern int repeat(void);
extern void run_test(void);

#endif
