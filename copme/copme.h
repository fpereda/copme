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

/**
 * @file copme.h
 * @brief Main header file for copme.
 */

#ifndef COPME_GUARD_COPME_H
#define COPME_GUARD_COPME_H 1

#define copme_foreach_group(s, g) \
	for (struct copme_group *g = (s)->groups; g->sdesc; g++)

#define copme_foreach_option(g, o) \
	for (struct copme_long *o = (g)->opts; o->lname; o++)

#define copme_foreach_group_option(s, g, o) \
	copme_foreach_group(s, g) \
		copme_foreach_option(g, o)

#define COPME_NOPTV_GROWTH_RATE (2.5)

/**
 * Holds information about an option argument.
 */
struct copme_arg {
	char *data;              /**< Data supplied by the user */
	unsigned specified : 1;  /**< Whether the argument was specified */
};

/**
 * Define whether an option has a required argument or not.
 */
enum copme_arg_kind {
	COPME_NOARG,   /**< No argument for this option */
	COPME_HASARG,  /**< Required argument for this option */
	COPME_OPTARG   /**< Optional argument for this option */
};

/**
 * Defines a long option.
 */
struct copme_long {
	char *lname;                   /**< Long name */
	char sname;                    /**< Short name */
	char *desc;                    /**< Description of the option */
	enum copme_arg_kind arg_kind;  /**< Define the kind of argument */
	struct copme_arg *arg;         /**< Pointer to our copme_arg */
	unsigned specified;            /**< Times this option was specified */
};

/**
 * Group of options.
 */
struct copme_group {
	char *sdesc;              /**< Short description or name of the group */
	char *ldesc;              /**< Long description of the group */
	struct copme_long *opts;  /**< Array of options belonging to this group */
};

/**
 * Arguments that weren't options.
 */
struct copme_nopts {
	unsigned count;  /**< Number of no options */
	char **noptv;    /**< Array of pointers to those no options */
	size_t size;     /**< Number of elements there is space allocated for */
};

/**
 * State of a copme parsing.
 */
struct copme_state {
	int argc;                    /**< Number of arguments */
	char **argv;                 /**< Array of arguments */
	unsigned argind;             /**< Current argument we are parsing */
	struct copme_nopts nopts;    /**< Store no options as we find them */
	struct copme_group *groups;  /**< Groups of options to recognize */
	struct copme_long *curopt;   /**< Current long option */
	unsigned finished : 1;       /**< Whether we are finished or not */
	unsigned error    : 1;       /**< Whether we are in error state */
};

/**
 * Gets a pointer to a copme_long in various groups given its name.
 *
 * @param groups Groups where the option is.
 * @param lname Long name identifying the option to find.
 * @return Pointer to said option or NULL if not found.
 */
struct copme_long *
copme_option_named(struct copme_group *groups, char *lname);

/**
 * Allocate and init a copme_state. A copme_state holds information about the
 * state of the library. This pointer should be freed with copme_free once the
 * caller is done with it.
 *
 * @see copme_free
 * @param groups Groups defining the options to extract
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @return Pointer to a copme_state holding a new parser.
 */
struct copme_state *
copme_init(struct copme_group groups[], int argc, char *argv[]);

/**
 * Completely free a copme_state. Once the client has finished parsing options
 * and extracting info, it should free the resources allocated for the parser
 * using this function.
 *
 * @param st Pointer to the parser to free.
 */
void copme_free(struct copme_state *st);

/**
 * Parse next option.
 *
 * @param st Pointer to the parser.
 */
void copme_next(struct copme_state *st);

/**
 * Display usage information for a parser.
 *
 * @param st Parser to show information for.
 * @param pre Function to call before displaying usage information.
 * @param post Function to call after everything has been displayed.
 */
void copme_usage(struct copme_state *st,
		void (*pre)(void), void (*post)(void));

/**
 * Whether a parser has finished or not.
 *
 * @param st Parser.
 * @return 0 if it has not finished. != 0 otherwise.
 */
static inline unsigned copme_finished(struct copme_state *st)
{
	return st->finished || st->argind >= st->argc;
}

/**
 * Whether the parser is in error state.
 *
 * @param st Parser.
 * @return 0 if it is not in error state. != 0 otherwise.
 */
static inline unsigned copme_error(struct copme_state *st)
{
	return st->error;
}

/**
 * Get a pointer to the current option parser.
 *
 * @param st Parser
 * @return Pointer to the current option.
 */
static inline struct copme_long *copme_current_opt(struct copme_state *st)
{
	return st->curopt;
}

/**
 * Get no options for a parser.
 *
 * @param st Parser
 * @return Pointer to a copme_nopts with information about no options found.
 */
static inline struct copme_nopts *copme_nopts(struct copme_state *st)
{
	return &st->nopts;
}

/**
 * Get extra params for a parser.
 *
 * @param st Parser in finished state.
 * @return Index of the first extra param (<tt>argv[index]</tt> might be
 * <tt>NULL</tt> if the last argument is <tt>--</tt>).
 */
static inline unsigned copme_extra(struct copme_state *st)
{
	return st->argind < 1 ? 1 : st->argind;
}

#endif
