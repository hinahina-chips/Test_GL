#ifndef SHADER_HPP
#define SHADER_HPP

#include <iostream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

#endif
