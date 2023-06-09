#ifndef COUNT_SORT_H
#define COUNT_SORT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <omp.h>

using namespace std;
int Range = 255;

// The main function that sorts the given map based on values
vector<string> countSort(map<string, int>& keyValueMap) {
    vector<string> output;
    int maxValue = 0;

    // Find the maximum value in the map
    for (const auto& kv : keyValueMap) {
        maxValue = max(maxValue, kv.second);
    }

    // Create a count array and initialize it to 0
    vector<int> count(maxValue + 1, 0);

    int counter = 1;
#pragma omp parallel num_threads(4)
    {
        std::map<std::string, int>::iterator it;
        int i, nthreads = omp_get_num_threads();
        int id = omp_get_thread_num();
        int n = keyValueMap.size();
        int start = id * n / nthreads;
        int end = (id + 1) * n / nthreads;
        if (id == nthreads - 1) end = n;

        std::map<std::string, int>::iterator start_iter = keyValueMap.begin();
        std::advance(start_iter, start);

        std::map<std::string, int>::iterator end_iter = keyValueMap.begin();
        std::advance(end_iter, end);

        for (it = start_iter, i = start; it != end_iter; ++it, ++i) {
#pragma omp critical
            {
                std::cout << "Threads: " << omp_get_thread_num() + 1 << " got data : " << it->first << std::endl;
                ++count[it->second];
                counter++;
            }
        }
    }

    // Modify count array to contain the actual positions
#pragma omp parallel for schedule(static, 4) num_threads(4)
    for (int i = 1; i <= maxValue; ++i) {
        count[i] += count[i - 1];
    }

    // Build the output vector
    output.resize(keyValueMap.size());
#pragma omp parallel num_threads(4)
    {
        std::map<std::string, int>::iterator kv;
        int i, nthreads = omp_get_num_threads();
        int id = omp_get_thread_num();
        int n = keyValueMap.size();
        int start = id * n / nthreads;
        int end = (id + 1) * n / nthreads;
        if (id == nthreads - 1) end = n;

        std::map<std::string, int>::iterator start_iter = keyValueMap.begin();
        std::advance(start_iter, start);

        std::map<std::string, int>::iterator end_iter = keyValueMap.begin();
        std::advance(end_iter, end);

        for (kv = start_iter; kv != end_iter; ++kv) {
            int index;
#pragma omp critical
            {
                index = --count[kv->second];
            }
#pragma omp critical
            {
                output[index] = kv->first;
            }
        }
    }
    return output;
}

#endif
