#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>


int width, height;
int main( void ){
    GLFWwindow* window;

    /* Init GLFW */
    if( !glfwInit() )
        exit( EXIT_FAILURE );

    window = glfwCreateWindow( 400, 400, "Boing (classic Amiga demo)", NULL, NULL );
    if (!window)
    {
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    glfwSetWindowAspectRatio(window, 1, 1);

    //glfwSetFramebufferSizeCallback(window, reshape);
    //glfwSetKeyCallback(window, key_callback);
    // glfwSetMouseButtonCallback(window, mouse_button_callback);
    //glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwGetProcAddress;
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval( 1 );

    glfwGetFramebufferSize(window, &width, &height);

    glfwSetTime( 0.0 );



    /* Main loop */
    for (;;)
    {

        glfwSwapBuffers(window);
        glfwPollEvents();

        /* Check if we are still running */
        if (glfwWindowShouldClose(window))
            break;
    }

    glfwTerminate();
    exit( EXIT_SUCCESS );
}