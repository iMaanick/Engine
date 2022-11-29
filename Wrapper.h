#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <functional>
class Wrapper {
public:
    template<typename Object, typename... Args>
    Wrapper(Object* obj, int(Object::* func)(Args...), const std::vector<std::pair<std::string, int>>& args) {
        if (obj == nullptr) {
            throw std::exception("wrapper: nullptr obj");
        }
        if (func == nullptr) {
            throw std::exception("wrapper: nullptr func");
        }
        for (const auto& arg : args) {
            arguments.insert(arg);
        }
        if (arguments.size() != args.size()) {
            throw std::exception("wrapper: Args name should be unique");
        }
        commandFunction = [this, obj, func](std::vector<int>& args) {
            return executeFunction(obj, func, args, std::make_index_sequence<sizeof...(Args)>{});
        };
    }
    Wrapper() = delete;
    ~Wrapper() = default;
    int execute(const std::vector<std::pair<std::string, int>>& args) {
        std::map<std::string, int> commandArgs;
        for (const auto& arg : args) {
            commandArgs.insert(arg);
        }
        if (commandArgs.size() != args.size()) {
            throw std::exception("wrapper::execute: Arg names should be unique");
        }
        if (commandArgs.size() != arguments.size()) {
            throw std::exception("wrapper::execute: Number of args in function != number of args you entered");
        }
        std::vector<int> commandArgsValues;
        for (const auto& elem : commandArgs) {
            if (!arguments.contains(elem.first)) {
                throw std::exception(("wrapper::execute: Arg name: " + elem.first + " does not exists in arguments").c_str());
            }
            commandArgsValues.push_back(elem.second);
        }
        return commandFunction(commandArgsValues);
    }
private:
    template<typename Object, typename... Args, size_t... Indxs>
    int executeFunction(Object* subj, int(Object::* func)(Args...), std::vector<int>& args, std::index_sequence<Indxs...>) {
        return ((subj->*func)(args[Indxs]...));

    }
    std::map<std::string, int> arguments;
    std::function<int(std::vector<int>&)> commandFunction;
};