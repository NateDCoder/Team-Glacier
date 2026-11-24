#pragma once
#include <vector>
#include <memory>
class Component;
class Graphics;

/// One machine: components kept in draw order.
class Machine {
private:
    int mMachineNumber;
    std::vector<std::shared_ptr<Component>> mComponents;
public:
    Machine(int machineNumber);
    void AddComponent(std::shared_ptr<Component> component);
    void Draw(Graphics graphics);
    void SetTime(double time);
    void Reset();
    int GetMachineNumber();
};
