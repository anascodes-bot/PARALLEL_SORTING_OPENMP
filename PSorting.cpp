#include "Header.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <omp.h>
#include <algorithm>

vector<string> countSort(map<string, int>& keyValueMap);


bool sortByValue(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    return a.second < b.second;
}

int main() {
    std::ifstream inputFile;
    inputFile.open("input2.txt");
    std::string line;
    std::map<std::string, int> keyValueMap;

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            std::istringstream iss(line);
            std::string token;
            while (getline(iss, token, ',')) {
                int value;
                if (token.size() == 1 && !isdigit(token[0])) {
                    value = static_cast<int>(token[0]);
                }
                else {
                    value = stoi(token);
                }
                keyValueMap[token] = value;
            }
        }
        inputFile.close();
    }
    else {
        std::cout << "Unable to open the input file." << std::endl;
        return 1;
    }
    //    std::vector<std::pair<std::string, int>> keyValueVector(keyValueMap.begin(), keyValueMap.end());
    //    std::sort(keyValueVector.begin(), keyValueVector.end(), sortByValue);
    //
    //#pragma omp parallel for schedule()
    //
    //    std::cout << "Sorted values:" << std::endl;
    //    for (const auto& kv : keyValueVector) {
    //        std::cout << kv.first << " -> " << kv.second << std::endl;
    //    }


    std::vector<std::string> results = countSort(keyValueMap);
    for (const auto& key : results)
    {
        std::cout << key << std::endl;
    }

    return 0;
}



