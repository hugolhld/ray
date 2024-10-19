#include <iostream>
#include "Color.hpp"
#include "Image.hpp"

using namespace std;


int main()
{    
    Color red(1, 0, 0);
    Color green(0, 1, 0);
    Color black;

    cout << "Red : " << red << std::endl;
    cout << "Green : " << green << std::endl;
    cout << "Black : " << black << std::endl;

    Color yellow = red + green;

    cout << "Yellow : " << yellow << std::endl;

    Image image(512, 512, yellow);
    image.WriteFile("test.png");
}
