#include "IDGenerator.h"

std::unordered_map<std::string, int> IDGenerator::nextIds;

int IDGenerator::generateId(const std::string& className) {
    if (nextIds.find(className) == nextIds.end()) {
        nextIds[className] = 1;
    }
    return nextIds[className]++;
}