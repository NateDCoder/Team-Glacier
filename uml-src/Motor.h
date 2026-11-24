#pragma once
#include "Component.h"
class Polygon;
class RotationSource;

/// Motor: static body plus a shaft (the Component polygon) that spins with time.
class Motor : public Component {
private:
    double speed;
    Polygon body;
    RotationSource source;
public:
    Motor(std::string name);
    void SetSpeed(double speed);
    RotationSource* GetSource();
    void Draw(Graphics graphics) override;
    void SetTime(double time) override;
    void Reset() override;
};
