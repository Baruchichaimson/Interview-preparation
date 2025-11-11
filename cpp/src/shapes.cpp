/**************************
 Exercise:  shapes
 Date: 	    03/11/25
 Developer: Baruch Haimson
 Reviewer:  
 Status:    Approved
***************************/
#include "shapes.hpp"
using namespace std;

Line::Line(int x, int y) : Shape(x, y) {}

void Line::Draw() const 
{
    cout << string(x, ' ') << "Line" << endl;
}

Circle::Circle(int x, int y) : Shape(x, y) {}

void Circle::Draw() const 
{
    cout << string(x, ' ') << "Circle" << endl;
}

Rectangle::Rectangle(int x, int y) : Shape(x, y) {}

void Rectangle::Draw() const 
{
    cout << string(x, ' ') << "Rectangle" << endl;
}

Square::Square(int x, int y) : Rectangle(x, y) {}

void Square::Draw() const 
{
    cout << string(x, ' ') << "Square" << endl;
}

void DrawShapes(const vector<Shape*>& shapes)
{
    for (size_t i = 0; i < shapes.size(); ++i) 
    {
        shapes[i]->Move(5);
        shapes[i]->Draw();
    }
}
