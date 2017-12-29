# 3DP - A lightweight program for 3D object loading and viewing using QT + OpenGL

## Overview

This program provides a tool to view 3D object (.obj or .off) together with its color, select some useful neighboring vertices or faces and operate the model like Gaussion filtering.

You can get the latest release from []().

## Functions in detailed

You can try it using demo files in `demo/`.

### Read 3D model from file (.obj/.off)

Click `File->Open` or the first tool button in tool bar, and then select an obj or off file.

Notice that the program only support obj and off file with vertices and faces in triangle.

### Axis and mesh

You can choose whether to show cordinate axis and mesh of face by checking and unchecking the checkboxes on the left of the UI.

### Load color file

Click `Edit->Color` and select a color file.

Notice that the `.txt` color file should have n lines where n reperesents the number of model faces and each line contains a double value to reperesent the color of that face.

In color selection dialog, you can choose color mode - original, continuous or descrete.

### Neighboring points of a point.

Click `Edit->Selection->Neighbor Points of a Point`, and input the point id.

![npop](https://github.com/MeteorKepler/3DP/raw/master/doc/image/npop.png)

### Neighboring faces of a point.

Click `Edit->Selection->Neighbor Faces of a Point`, and input the point id.

![nfop](https://github.com/MeteorKepler/3DP/raw/master/doc/image/nfop.png)

### Neighboring faces of a face.

Click `Edit->Selection->Neighbor Faces of a Face`, and input the face id.

![nfof](https://github.com/MeteorKepler/3DP/raw/master/doc/image/nfof.png)

### Select an area of a list of Points

Click `Edit->Selection->Rigion from Points`, and input the points id.

![aop](https://github.com/MeteorKepler/3DP/raw/master/doc/image/aop.png)

### Draw normal line of a face

Click `Draw->Normal Vector->From face`, and input the point id.

![nof](https://github.com/MeteorKepler/3DP/raw/master/doc/image/nof.png)

### Noise

Always Remember you can check the check boxes on the middle left of the program to show or hide the model about noise and denoise discussed below.

You can add a normal noise to the model by clicking `Functions->Add Noise` and input the deviation.

![an](https://github.com/MeteorKepler/3DP/raw/master/doc/image/an.png)

Now you can use Gaussion filter to denoise the model by clicking `Functions->Denoising` and input the sigma parameter.

![dn](https://github.com/MeteorKepler/3DP/raw/master/doc/image/dn.png)

You can also compute the Mean Square Error(MSE) between the denoised model and the original model by clicking `Functions->MSE`. There will be a heat map indicating error at each face (blue is low and red is high).

![mse](https://github.com/MeteorKepler/3DP/raw/master/doc/image/mse.png)

You can clear the model above using `Functions->Clear`.
