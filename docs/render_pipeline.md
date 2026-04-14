the render pipeline use small steps to render a triangle:

to render your first triangle you need create a **Triangle** struct in **World space**
# for the triangle you need:
* internal texture and warning: the texture is triangular
* you need it have a texture in **external_texture** because render use this texture to render the triangle
* and you need set the **UV** and **Vexter position in global space**

# after this:
* create scanline and zbuffer (with same size)
* create a cam
* store your triangle in a std::vector
* call render
* show the viewport (if you dont using a graphical lib use the **Display** class)