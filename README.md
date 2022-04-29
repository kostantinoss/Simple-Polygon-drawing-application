# Polygon drawing application
Developed as part of the course [MYY702](https://www.cs.uoi.gr/course/computer-graphics-and-interactive-systems/?lang=en)

### Before you start
Make sure that you have a version of GNU Compiler up and running.

To install GLUT dependancies, run the following commands 
```
sudo apt install libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev
sudo apt install freeglut3-dev
```
### Compile
There is a Makefile included that does all the work.
```
~$ make
```

## Drawing Polygons
To begin, right click and select ACTION>Polygon.
The start clicking o the white workspace to create your first polygon. The applications support only non-ontersecting polygons, so for example if you tried to construct a bow tie polygon and cross some existong edge, the shape constructed until that moment will disappear. On the menu (right-click) there are options that allow you to choose color for the polygon's outline and fill.

![drawing_1](https://github.com/kostantinoss/graphics/blob/5df73eba5fabccffb565830f4849aeb89fa680d0/screenshots/Screenshot%20from%202022-04-29%2019-37-57.png)
![drawing_2](https://github.com/kostantinoss/graphics/blob/10a8a6e3d99a0a36295a561ad3f282c4dfc98856/screenshots/Screenshot%20from%202022-04-29%2019-38-02.png)
![drawing_3](https://github.com/kostantinoss/graphics/blob/10a8a6e3d99a0a36295a561ad3f282c4dfc98856/screenshots/Screenshot%20from%202022-04-29%2019-38-07.png)

## Clip Polygons
Fist draw some polygons. Then, right-click to open the menu, select ACTION> Clip Polygons and drag the mouse ehile holding the left-click down in order do define the clipping area as shown in the pictures. 
![clipping_1](https://github.com/kostantinoss/graphics/blob/bdceffef1a735611e36d6d5dc2ad3bbae6e5f5ea/screenshots/Screenshot%20from%202022-04-29%2019-42-46.png)
![clipping_2](https://github.com/kostantinoss/graphics/blob/bdceffef1a735611e36d6d5dc2ad3bbae6e5f5ea/screenshots/Screenshot%20from%202022-04-29%2019-42-52.png)

## 3D conversion
From the menu select ACTION>Extrude. You can controll the objects using the arrow keys.

![3d_1](https://github.com/kostantinoss/graphics/blob/bdceffef1a735611e36d6d5dc2ad3bbae6e5f5ea/screenshots/Screenshot%20from%202022-04-29%2019-44-35.png)
![3d_2](https://github.com/kostantinoss/graphics/blob/bdceffef1a735611e36d6d5dc2ad3bbae6e5f5ea/screenshots/Screenshot%20from%202022-04-29%2019-44-59.png)
![3d_3](https://github.com/kostantinoss/graphics/blob/bdceffef1a735611e36d6d5dc2ad3bbae6e5f5ea/screenshots/Screenshot%20from%202022-04-29%2019-45-28.png)
