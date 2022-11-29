#pragma once
#include "Engine.h"
class A {
public:
    int sum(int a, int b, int c) {
        return a + b + c;
    }
};

class B {
public:
    int subtract(int a, int b) {
        return a - b;
    }
};

int main() {
    try {
        A a;
        Wrapper wrapper(&a, &A::sum, { {"arg1", 1}, {"arg2", 2}, {"arg3", 3} });
        B b;
        Wrapper wrapper2(&b, &B::subtract, { {"arg1", 1}, {"arg2", 2} });
        Engine engine;
        engine.registerCommand(&wrapper, "sum");
        engine.registerCommand(&wrapper2, "subtract");
        std::cout << engine.execute("sum", { {"arg1", 1}, {"arg2", 5}, {"arg3", 5} }) << std::endl;
        std::cout << engine.execute("subtract", { {"arg1", 1}, {"arg2", 5} }) << std::endl;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}