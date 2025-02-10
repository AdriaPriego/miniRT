<p align="center">
	<img alt="GitHub Repo stars" src="https://img.shields.io/github/stars/ferri17/miniRT?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/ferri17/miniRT" />
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/ferri17/miniRT?color=red" />
	<img alt="GitHub last commit (by committer)" src="https://img.shields.io/github/last-commit/ferri17/miniRT" />
	<img alt="MacOS compatibility" src="https://img.shields.io/badge/macOS-compatible-brightgreen.svg" />
</p>

<h3 align="center">MiniRT(raytracer) 42 school project</h3>

  <p align="center">
    The goal of this project is to learn the fundamentals of raytracing by building a CPU raytracer from scratch in C language.
    <br />
  </p>
</div>

<!-- ABOUT THE PROJECT -->
## About The Project

![MiniRT demo intro](https://github.com/ferri17/miniRT/assets/19575860/3db2722c-1763-4388-b290-17a412263a0d)

**MiniRT (raytracer)** is the second **computer graphics** project in 42 school common core. The program must read .rt files (more on the file format below) and render simple scenes with camera, lights, planes, spheres, cylinders and cones (this raytracer is not triangle based so all objects are defined by it's matematical formulas).

<h3>What is supported?</h3>
<ul>
  <li>Camera setting</li>
  <li>4 basic objects: Plane, Sphere, Cylinder, Cone</li>
  <li>Multiple lights, including ambient light</li>
  <li>Phong reflection model: Ambient + Diffuse + Specular</li>
  <li>Checkerboard pattern</li>
  <li>Bitmap diffuse textures</li>
  <li>Normal map textures</li>
</ul>

<!-- GETTING STARTED -->
## Getting Started
In order to run the program first clone the repository:
```bash
git@github.com:ferri17/miniRT.git
```
Open the folder:
```bash
cd miniRT/
```
Compile the program:
```bash
make
```
Run the program with a valid scene as argument(test scenes can be found in /scenes)
```bash
./miniRT scenes/_test.rt
```

<!-- Controls -->
## Controls
| Action                          | Key                      |
| :---                          | :----:                     |
| Select object                 | Mouse left click           |
| Move selected object          | A,S,D,W,1,2                |
| Switch Render mode / Edit mode| M                          |
| Bottom screen slider          | Change camera's FOV        |

<!-- GALLERY -->
## Gallery

<img width="891" alt="Screenshot 2024-02-28 at 01 20 12" src="https://github.com/ferri17/miniRT/assets/19575860/032cc2bd-befa-4969-80ac-45bd8dd6f720">
<img width="895" alt="Screenshot 2024-02-28 at 01 20 37" src="https://github.com/ferri17/miniRT/assets/19575860/637b8e90-0e1b-4d81-86a3-65c47b2a33f4">
<img width="894" alt="Screenshot 2024-02-28 at 01 21 38" src="https://github.com/ferri17/miniRT/assets/19575860/0a14ef7d-b497-40ed-a0b0-89ef66849cb3">



<!---
Here is an example of a simple scene:
```
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0 10 10  0  0 10 10  0  0  0 10 10 10 10 10  0  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10 10 10 10 10  0  0  0  0 10 10 10 10  0  0  0
0  0  0 10 10 10 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10 10 10 10 10  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
```
Each number represents a point in space:
* The horizontal position corresponds to its axis.
* The vertical position corresponds to its ordinate.
* The value corresponds to its altitude.
-->
<!-- GETTING STARTED 
## Getting Started
In order to run the program first clone the repository:
```bash
git clone git@github.com:ferri17/FdF.git
```
Open the folder:
```bash
cd FdF/
```
Compile the program:
```bash
make
```
Run the program with a valid map as argument(test maps can be found in /maps)
```bash
./fdf maps/42.fdf
```
-->

<!-- Controls 
## Controls
| Action                          | Key                      |
| :---                          | :----:                     |
| Mouse right click + drag      | Move map                   |
| Mouse left click + drag       | Rotate map                 |
| Lock rotation axis            | Hold X,Y,Z while rotating  |
| Color themes                  | 1, 2, 3                    |
| Change map heights            | N,M                        |
| Edge/Vertex mode              | G                          |
| Snap rotation                 | Hold H while rotating      |
| Isometric/Paralel projection  | I,P                        |
-->
<!-- Gallery 
## Gallery
<img width="1400" alt="Screen Shot 2023-08-10 at 3 30 30 PM" src="https://github.com/ferri17/FdF/assets/19575860/d131a52b-1bb3-4bdd-ba8a-9dfb42620446">
<img width="1396" alt="Screen Shot 2023-08-10 at 5 38 26 PM" src="https://github.com/ferri17/FdF/assets/19575860/ae64c1b0-6fe0-4f4a-8e3d-833ed7cfa393">
<img width="1397" alt="Screen Shot 2023-08-10 at 5 37 03 PM" src="https://github.com/ferri17/FdF/assets/19575860/e621e9ee-2ea8-4eaa-a51c-92b53e6e87c6">
-->
<!-- Resources
## Resources

**Minilibx**

Really good guides to start using minilibx functions.
* https://gontjarow.github.io/MiniLibX/mlx-tutorial-create-image.html
* https://harm-smits.github.io/42docs/libs/minilibx/images.html

**How to draw a line in a pixel map**
* https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

**How to represent a 3D figure in a 2D space**
* https://www.youtube.com/watch?v=p4Iz0XJY-Qk
* https://en.wikipedia.org/wiki/Rotation_matrix
* https://clintbellanger.net/articles/isometric_math/
  
**Gradients**

Best walkthrough to understand how to calculate a gradient between 2 points
* https://dev.to/freerangepixels/a-probably-terrible-way-to-render-gradients-1p3n
  
**Virtual keys macOS**
* https://stackoverflow.com/questions/3202629/where-can-i-find-a-list-of-mac-virtual-key-codes

**Clipping lines to optimise render with Cohen-Sutherland algorithm**
* https://www.geeksforgeeks.org/line-clipping-set-1-cohen-sutherland-algorithm/

-->
