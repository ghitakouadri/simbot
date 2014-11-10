/*
    simbot is a simulator of a 2 wheels differential drive robot.
    Copyright (C) 2014 Roberto Cometti <modsrm@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

    You can find the full license document in the root of this repository
    or online at <http://www.gnu.org/licenses/gpl-2.0.html>
*/

#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

static void error_callback(int, const char*);

int main()
{
    printf( "This is SimBot!\n" );

    // Set error callback for glfw.
    glfwSetErrorCallback(error_callback);

    // Initialize glfw.
    if( glfwInit() != GL_TRUE )
    {
        exit(EXIT_FAILURE);
    }

    // Create main windows.
    GLFWwindow *window = glfwCreateWindow(800, 600, "SimBot", NULL, NULL);

    while(1)
    {
        __asm("pause");
    }

    // Terminate glfw.
    glfwTerminate();
}

static void error_callback(int err_code, const char* description)
{
    fputs(description, stderr);
}

