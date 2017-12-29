# 3DP - A lightweight program for 3D object loading and viewing

#### This project is based on QT and OpenGL

## Overview

This program provides a tool to view 3D object (.obj or .off) together with its color, select some useful neighboring vertices or faces and operate the model like Gaussion filtering.

You can get the latest release from []().

## Functions in detailed

You can try it using demo files in `demo/`.

### Read 3D model from file (.obj/.off)

Click `File->Open` or the first tool button in tool bar, and then select an obj or off file.

Notice that the program only support obj and off file with vertices and faces in triangle.

### Load color file

Click `Edit->Color` and select a color file.

Notice that the `.txt` color file should have n lines where n reperesents the number of model faces and each line contains a double value to reperesent the color of that face.

In color selection dialog, you can choose color mode - original, continuous or descrete.

### Neighboring points of a point.

Click `Edit->Selection->Neighbor Points of a Point`, and input the point id.
