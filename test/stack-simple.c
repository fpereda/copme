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

#include "stack.h"

#define SIZEOF_ARRAY(a) (sizeof(a)/sizeof(a[0]))

char *name(void)
{
    static char n[] = "stack data type";
    return n;
}

int repeat(void)
{
    return 1;
}

void run_test(void)
{
    stack *s = stack_alloc_init(NULL);
	CTME_CHECK(stack_empty(s));
	CTME_CHECK_EQUAL(stack_peek(s), NULL);
	stack_destroy(s);

	s = stack_alloc_init(NULL);
	double a = 3;
	double *pa = &a;

	stack_push(s, pa);
	CTME_CHECK_EQUAL(stack_peek(s), pa);
	CTME_CHECK_EQUAL(stack_size(s), 1);

	double *paa = stack_pop(s);
	CTME_CHECK_EQUAL(paa, pa);
	CTME_CHECK_EQUAL(stack_size(s), 0);
	CTME_CHECK_EQUAL(stack_peek(s), NULL);

	unsigned ten[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	unsigned i;
	for (i = 0; i < SIZEOF_ARRAY(ten); i++)
		stack_push(s, ten + i);

	CTME_CHECK_EQUAL(stack_size(s), SIZEOF_ARRAY(ten));

	for (i = 0; i < SIZEOF_ARRAY(ten); i++) {
		unsigned os = stack_size(s);
		unsigned *pi = stack_pop(s);
		unsigned ns = stack_size(s);
		CTME_CHECK(os > ns);
		CTME_CHECK_EQUAL(pi, ten + SIZEOF_ARRAY(ten) - i - 1);
	}

	CTME_CHECK_EQUAL(stack_size(s), 0);
	CTME_CHECK_EQUAL(stack_peek(s), NULL);
	stack_destroy(s);
}
