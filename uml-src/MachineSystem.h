#pragma once
#include <memory>
#include <string>
class Machine;
class Point;
class Graphics;

/// Implements IMachineSystem. Holds exactly one Machine at a time.
class MachineSystem {
private:
    std::shared_ptr<Machine> mMachine;
    std::string mResourcesDir;
    Point mLocation;
    double mFrameRate;
    int mFrame;
    double mMachineTime;
public:
    MachineSystem(std::string resourcesDir);
    void SetLocation(Point location);
    Point GetLocation();
    void DrawMachine(Graphics graphics);
    void SetMachineFrame(int frame);
    void SetMachineNumber(int machine);
    int GetMachineNumber();
    void SetFrameRate(double rate);
    double GetMachineTime();
    void SetFlag(int flag);
    void ChooseFactory(int machine);
};
