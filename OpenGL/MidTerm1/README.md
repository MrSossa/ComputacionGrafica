This is a computer graphics mid-term made with glut.
The objective was to do a t-shirt where we can use multiple transformations like translation, rotation, and escalation. To these transformations I didn't use OpenGL functions, I made my matrix operations using Eigen.
To use this application we need Eigen downloaded and Flut installed, after that, we compile TShirt.cpp file with the next command:
$ g++ -I eigen-3.4.0/ -o TShirt TShirt.cpp -lGL -lGLU -lglut
This command generates an executable program.

How to use:
When we execute the TShirt program we can set the length of TShirt and transformations values, all values can be floats.