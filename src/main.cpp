#include "Shader.h"
#include "Point.h"

#include "app.h"
#include <iostream>

const GLuint WIDTH = 1600, HEIGHT = 1600;

int main(int argc, char* argv[])
{
    app m_app;
    m_app.Init(WIDTH, HEIGHT);
    m_app.Run();
    return 0;
}