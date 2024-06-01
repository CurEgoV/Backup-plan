#include <unordered_map>
#include <string>

#ifndef IDGENERATOR_H
#define IDGENERATOR_H

class IDGenerator {
private:
    static std::unordered_map<std::string, int> nextIds;

public:
    static int generateId(const std::string& className);
};

#endif