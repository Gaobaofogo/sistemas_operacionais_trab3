#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


struct ConfigData {
    int initPosition;
    int queueSize;
    std::vector<int> cylinders;
};

void readFile(ConfigData* config);


int main(int argc, char *argv[]) {
    ConfigData config;
    config.initPosition = 0;
    config.queueSize = 0;

    readFile(&config);

    return 0;
}

void insertValuesOnCylinder(ConfigData* config, std::string line) {
    int kCylinderSize = line.size() + 1;
    char cylinderValues[kCylinderSize];

    snprintf(cylinderValues, line.size() + 1, "%s", line.c_str());

    char* rest = cylinderValues;
    char* token = strtok_r(rest, " ", &rest);

    for (int i = 0; i < config->queueSize; ++i) {
        std::cout << atoi(token) << std::endl;
        config->cylinders.push_back(atoi(token));
        token = strtok_r(rest, " ", &rest);
    }
}

void readFile(ConfigData* config) {
    std::ifstream file("config.txt", std::ifstream::in);

    if (file.bad()) {
        perror("Erro ao abrir o arquivo.");
        std::exit(1);
    }

    std::string line;
    int count = 0;

    while (std::getline(file, line)) {
        switch (count) {
            case 0:
                config->initPosition = stoi(line);
                break;
            case 1:
                config->queueSize = stoi(line);
                break;
            case 2:
                insertValuesOnCylinder(config, line);
                break;
        }

        ++count;
    }

    file.close();
}
