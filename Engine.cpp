#include "Engine.h"
void Engine::registerCommand(Wrapper* wrapper, const std::string& commandName) {
    if (wrapper == nullptr) {
        throw std::exception("Engine::registerCommand: nullptr wrapper");
    }
    if (commands.contains(commandName)) {
        throw std::exception(("Engine::registerCommand: this command: " + commandName + " is already exists in Engine, change command name").c_str());
    }
    commands[commandName] = wrapper;
}
int Engine::execute(const std::string& commandName, const std::vector<std::pair<std::string, int>>& args) {
    if (!commands.contains(commandName)) {
        throw std::exception(("Engine::execute: this command: " + commandName + " does not exist in Engine").c_str());
    }
    return (commands[commandName]->execute)(args);
}