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
#include <stdlib.h>
#include <unistd.h>

#include "copme.h"

int main(int argc, char *argv[])
{
	unsigned depth = 0;
	char *axiom = "F";

	struct copme_arg a_depth = {0, 0};
	struct copme_arg a_axiom = {0, 0};
	struct copme_arg a_multi = {0, 0};
	struct copme_arg a_optional = {0, 0};

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

	struct copme_state *cst = copme_init(opts, argc, argv);
	while (! copme_finished(cst)) {
		copme_next(cst);

		if (a_multi.specified) {
			a_multi.specified = 0;
			printf("MULTI! %s\n", copme_arg(cst));
		}

		if (copme_error(cst))
			return EXIT_FAILURE;
		if (o_help->specified) {
			copme_usage(cst);
			return EXIT_SUCCESS;
		}
	}

	if (a_depth.specified)
		depth = atoi(a_depth.data);
	if (a_axiom.specified)
		axiom = a_axiom.data;

	if (o_multi->specified)
		putchar('\n');

	printf("%d multi\ndepth = %d\naxiom = %s\n",
			o_multi->specified, depth, axiom);

	if (o_optional->specified)
		printf("OPTIONAL : %s\n",
				a_optional.specified ? a_optional.data : "no arg");

	free(cst);

	return EXIT_SUCCESS;
}
