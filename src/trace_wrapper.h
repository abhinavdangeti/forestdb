/* -*- Mode: C++; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/*
 *     Copyright 2016 Couchbase, Inc
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#pragma once

#ifdef _PHOSPHOR_LIB_AVAILABLE
#include <phosphor/phosphor.h>
#else

// Synchronous events
#define TRACE_EVENT_START(category, name, ...)
#define TRACE_EVENT_START0(category, name)
#define TRACE_EVENT_END(category, name, ...)
#define TRACE_EVENT_END0(category, name)

// Scoped events
#define TRACE_EVENT(category, name, ...)
#define TRACE_EVENT0(category, name)

// Asynchronous events
#define TRACE_ASYNC_START(category, name, id, ...)
#define TRACE_ASYNC_START0(category, name, id)
#define TRACE_ASYNC_END(category, name, id, ...)
#define TRACE_ASYNC_END0(category, name, id)

// Instant events
#define TRACE_INSTANT(category, name, ...)
#define TRACE_INSTANT0(category, name)

// Global events
#define TRACE_GLOBAL(category, name, ...)
#define TRACE_GLOBAL0(category, name)

#endif
