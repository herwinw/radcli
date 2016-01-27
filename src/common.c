/*
 * Copyright (c) 1998 The NetBSD Foundation, Inc.
 *
 * Copyright (C) 1995,1996,1997 Lars Fenneberg
 *
 * Copyright 1992 Livingston Enterprises, Inc.
 *
 * Copyright 1992,1993, 1994,1995 The Regents of the University of Michigan
 * and Merit Network, Inc. All Rights Reserved
 *
 * See the file COPYRIGHT for the respective terms and conditions.
 * If the file is missing contact me at lf@elemental.net
 * and I'll send you a copy.
 *
 */

#include <sys/time.h>

#include <config.h>
#include <includes.h>
#include <radcli/radcli.h>

#define	RC_BUFSIZ	1024

/** Get next line from the stream.
 *
 * @param fp a %FILE pointer.
 * @param len output length.
 * @return the next line in an allocated buffer.
 */
char *
rc_fgetln(FILE *fp, size_t *len)
{
	static char *buf = NULL;
	static size_t bufsiz = 0;
	char *ptr;

	if (buf == NULL) {
		bufsiz = RC_BUFSIZ;
		if ((buf = malloc(bufsiz)) == NULL)
			return NULL;
	}

	if (fgets(buf, (int)bufsiz, fp) == NULL)
		return NULL;
	*len = 0;

	while ((ptr = strchr(&buf[*len], '\n')) == NULL) {
		size_t nbufsiz = bufsiz + RC_BUFSIZ;
		char *nbuf = realloc(buf, nbufsiz);

		if (nbuf == NULL) {
			int oerrno = errno;
			free(buf);
			errno = oerrno;
			buf = NULL;
			return NULL;
		} else
			buf = nbuf;

		*len = bufsiz;
		if (fgets(&buf[bufsiz], RC_BUFSIZ, fp) == NULL)
			return buf;

		bufsiz = nbufsiz;
	}

	*len = (ptr - buf) + 1;
	return buf;
}
