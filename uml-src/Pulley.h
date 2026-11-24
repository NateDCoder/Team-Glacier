#pragma once
#include "Component.h"
class RotationSink;
class RotationSource;

/// Pulley: both a sink (driven) and a source (drives other parts).
class Pulley : public Component {
private:
    double radius;
    RotationSink sink;
    RotationSource source;
public:
    Pulley(std::string name, double radius);
    void Draw(Graphics graphics) override;
    void SetRotation(double rotation) override;
    double GetRadius();
    RotationSource* GetSource();
    RotationSink* GetSink();
};
