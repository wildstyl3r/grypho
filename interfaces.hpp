#include <iostream>

class Displayable 
{
public:
    virtual ostream& operator<< (ostream& os) const = 0;
};
