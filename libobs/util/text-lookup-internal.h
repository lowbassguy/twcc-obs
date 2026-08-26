/*
 * Copyright (c) 2026 The Web Creative Community
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#pragma once

#include "text-lookup.h"

#ifdef __cplusplus
extern "C" {
#endif

bool text_lookup_replace(lookup_t *lookup, const char *lookup_val, const char *from, const char *to);

#ifdef __cplusplus
}
#endif
