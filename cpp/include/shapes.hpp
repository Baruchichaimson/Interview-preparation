/**************************
 Exercise:  shapes
 Date: 	    03/11/25
 Developer: Baruch Haimson
 Reviewer:  
 Status:    Approved
***************************/
#ifndef __SHAPES_HPP__
#define __SHAPES_HPP__

#include <iostream>
#include <vector>
#include <string>

class Shape {
protected: // not bakonventzia ach sheli 
    int x, y;

public:
    Shape(int x = 0, int y = 0) : x(x), y(y) {}
    virtual ~Shape() {}

    virtual void Draw() const = 0;
    virtual void Move(int dx) 
    {
        x += dx;
    }
};

class Line : public Shape 
{
public:
    Line(int x = 0, int y = 0);
    void Draw() const ;
};

class Circle : public Shape 
{
public:
    Circle(int x = 0, int y = 0);
    void Draw() const ;
};

class Rectangle : public Shape 
{
public:
    Rectangle(int x = 0, int y = 0);
    void Draw() const ;
};

class Square : public Rectangle 
{
public:
    Square(int x = 0, int y = 0);
    void Draw() const ;
};

void DrawShapes(const std::vector<Shape*>& shapes);

#endif // SHAPES_HPP
