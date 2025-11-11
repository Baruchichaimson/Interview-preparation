/**************************
 Exercise:  shapes
 Date: 	    03/11/25
 Developer: Baruch Haimson
 Reviewer:  
 Status:    Approved
***************************/
#include <vector>

#include "shapes.hpp"

int main()
{
    std::vector<Shape*> shapes;

    shapes.push_back(new Line());
    shapes.push_back(new Circle(5));
    shapes.push_back(new Rectangle(10));
    shapes.push_back(new Square(15));

    DrawShapes(shapes);

    for (size_t i = 0; i < shapes.size(); ++i) 
    {
        delete shapes[i];
    }

    return 0;
}
