#pragma once
#include "Wrapper.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <functional>
class Engine {
public:
    void registerCommand(Wrapper* wrapper, const std::string& commandName);
    int execute(const std::string& commandName, const std::vector<std::pair<std::string, int>>& args);
private:
    std::map< std::string, Wrapper*> commands;
};