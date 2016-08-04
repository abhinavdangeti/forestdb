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

#include <trace_wrapper.h>

std::mutex TraceMgr::initGuard;
std::atomic<TraceMgr *> TraceMgr::instance(nullptr);

TraceMgr* TraceMgr::get(void) {
    auto *tmp = instance.load();
    if (tmp == nullptr) {
        std::lock_guard<std::mutex> lock(initGuard);
        tmp = instance.load();
        if (tmp == nullptr) {
            // Second check under lock - to ensure that an instance is not
            // create twice by two threads if it were null.
            tmp = new TraceMgr();
            instance.store(tmp);
        }
    }
    return tmp;
}

void TraceMgr::shutdown(void) {
    std::lock_guard<std::mutex> lock(initGuard);
    auto *tmp = instance.load();
    if (tmp != nullptr) {
        delete tmp;
        instance = nullptr;
    }
}

TraceMgr::TraceMgr()
    : options(0x0000) { }

TraceMgr::~TraceMgr() { }

void TraceMgr::setOption(fdb_trace_option_t opt) {
    options.fetch_or(opt);
}

void TraceMgr::clearOptions() {
    options.store(0x0000);
}

bool TraceMgr::doTrace(fdb_trace_option_t opt) {
    if (opt & options.load()) {
        return true;
    } else {
        return false;
    }
}
