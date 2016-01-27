/*
 * Copyright (C) 2014 Nikos Mavrogiannopoulos
 *
 * See the file COPYRIGHT for the respective terms and conditions.
 *
 */

#ifndef COMMON_H
#define COMMON_H

#include <freeradius-client.h>

char * rc_fgetln(FILE *fp, size_t *len);

#endif
