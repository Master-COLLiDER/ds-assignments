#ifndef POINT_H
#define POINT_H


class Point {
    float x,y,z;
public:
    static float sqRoot(float);

    float distance(Point);

    Point(float x, float y, float z);

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    float getZ() const;

    void setZ(float z);
};


#endif //POINT_H
