#pragma once
#include "Component.h"
#include <vector>
class Snowflake;
class RotationSink;

/// Snow blower: does not spin; the driven rotation sets the snow output rate.
class SnowBlower : public Component {
private:
    double outputRate;
    double lastTime;
    RotationSink sink;
    std::vector<Snowflake> snowflakes;
public:
    SnowBlower(std::string name);
    void Draw(Graphics graphics) override;
    void SetRotation(double rotation) override;
    void SetTime(double time) override;
    void Reset() override;
    RotationSink* GetSink();
};
