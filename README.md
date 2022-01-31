# opengl-sandbox
Sandbox for testing out modern OpenGL and abstraction into classes. Includes testing on a related geometry library.

Built using Visual Studio 2022.

# Dependencies
1. GLFW - 3.3.6 (https://www.glfw.org/)
2. GLEW - 2.1.0 (http://glew.sourceforge.net/)
3. Eigen - 3.4.0 (https://eigen.tuxfamily.org/index.php?title=Main_Page)

Currently added into the solution directory under a "Dependencies" folder:

```
+-- $(SolutionDir)Dependencies/
|   +--eigen-3.4.0
|      +--Eigen (only this folder is necessary)
|   +--glew-2.1.0
|   +--GLFW
```

# Graphics

main.cpp - for sandbox testing.

## Drawables

Contains drawable classes which handles all GL calls for a single piece of geometry.

This may expand to specific pieces of geometry.

## Shaders

No formed thoughts on how this might look ultimately. Don't know the tradeoffs between reading in shader files on the fly vs compiling the shader code in with the rest of the code.

Less dependencies/resources needed to be packaged if compiled in.

# Geometry
Geometry classes, every geometry is made up of two components:
1. The physical definition
2. The transformation

What this means is that all geometry exists relative to the origin (0, 0, 0). Geometries can be placed via transformations applied onto the physical shape and is stored as a quaternion (TBD or some other transformation matrix).

## Basic Components

### Point

Single location.

Something like a circle or a sphere can be defined as a point and some radius value.

### Edge

Contains start and end points, this implicitly defines the order in which to draw the edge.

All shapes will have edges.

Derived classes could be straight or curved lines.

### Shape

Contains a series of points and edges that defines some geometry shape.

Basic shapes that can derive from this: Triangle, Rectangle, Circle

## Thoughts

Triangle - currently defined as 3 points, special cases like equilateral and iscoceles triangles can be defined as an origin point and some constant length and height values by the user, backend code can calculate the 3 points when necessary.

Rectangle - currently defined as 4 points, should really be a width and a height with some transformation.

Circle - defined as a radius with some transformation.