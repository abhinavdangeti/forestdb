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

#include <stdio.h>
#include <assert.h>

#include <vector>

typedef struct {
    std::string name;
    std::vector<uint64_t> latencies;
} stat_history_t;

template<typename T>
struct Stats {
    std::string name;
    double mean;
    double median;
    double stddev;
    double pct5;
    double pct95;
    double pct99;
    std::vector<T>* values;
};

class StatAggregator {
public:
    StatAggregator(int _num_stats, int _num_samples);

    ~StatAggregator();

    void aggregateAndPrintStats(const char* title, int count, const char* unit);

    stat_history_t** t_stats;

private:

    template<typename T>
    void printValues(std::vector<std::pair<std::string, std::vector<T>*> > values,
                     std::string unit);

    void fillLineWith(const char c, int spaces);

    int num_stats;
    int num_samples;
};
