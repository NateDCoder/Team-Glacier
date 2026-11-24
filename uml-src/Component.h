#pragma once
#include <string>
class Polygon;
class Point;
class Graphics;

/// Abstract base of every machine part. Owns the Polygon that receives rotation.
class Component {
private:
    std::string name;
    Point position;
    Polygon polygon;
public:
    Component(std::string name);
    virtual ~Component();
    virtual void Draw(Graphics graphics);
    virtual void SetRotation(double rotation);
    virtual void SetTime(double time);
    virtual void Reset();
    void SetPosition(Point position);
    Point GetPosition();
    Point RotatePoint(Point point, double angle);
};
