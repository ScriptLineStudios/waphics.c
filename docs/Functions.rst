Functions
================================

.. code-block:: c

  Rectangle waphics_rectangle_new(int x, int y, int width, int height);

Returns a new Rectangle with the specifed x, y, width and height.

.. code-block:: c

  Circle waphics_circle_new(int x, int y, int radius);

Returns a new Circle with the specified x, y and radius.

.. code-block:: c

  Surface waphics_display_new(uint32_t *pixels, unsigned int width, unsigned int height);

Returns a new Surface.

.. note::

  All functions which return a new instance of a strcture have corrosponding macros:
  
  .. code-block:: c

    #define RECT(x, y, w, h) waphics_rectangle_new(x, y, w, h)
    #define CIRCLE(x, y, r) waphics_circle_new(x, y, r)
    #define VECTOR2(x, y) waphics_vector2_new(x, y, z)
    #define SCREEN(pixels, w, h) waphics_display_new(pixels, w, h)

.. code-block:: c

  void waphics_fill_display(Surface display, uint32_t color);

Fills the specified Surface with the specified color

.. note::
  
  Colors should be in the following format:
  0xAABBGGRR
  
  Alternatily the RGBA or RGB macros can be used:
  
  .. code-block:: c
  
    #define RGBA(r, g, b, a) ((((r)&0xFF)<<(8*0)) | (((g)&0xFF)<<(8*1)) | (((b)&0xFF)<<(8*2)) | (((a)&0xFF)<<(8*3)))
    #define RGB(r, g, b) ((((r)&0xFF)<<(8*0)) | (((g)&0xFF)<<(8*1)) | (((b)&0xFF)<<(8*2)) | (((255)&0xFF)<<(8*3)))

.. code-block:: c

  void waphics_draw_rect(Surface display, Rectangle rect, uint32_t color);

Draws a rectangle with the given color 

.. code-block:: c

  void waphics_draw_line(Surface display, int x1, int y1, int x2, int y2, int color);

Draws a line from point (x1, y1) to (x2, y2)

.. code-block:: c

  void waphics_draw_circle(Surface display, Circle circle, uint32_t color);

Draws a circle from the given Circle instance.

.. code-block:: c

  void waphics_draw_triangle(Surface display, Vector2 p1, Vector2 p2, Vector2 p3, uint32_t color);

Draws a triangle with points (x1, y1); (x2, y2); (x3, y3) with a flat color.

.. code-block:: c

  void waphics_draw_triangle_3(Surface display, Vector2 p1, Vector2 p2, Vector2 p3, uint32_t color1, uint32_t color2, uint32_t color3);

Draws a triangle with points (x1, y1); (x2, y2); (x3, y3) with a barycentric color interpolation between the 3 colors.

.. code-block:: c

  void waphics_draw_image(Surface display, Rectangle rect,
          uint32_t scale, uint32_t *pixels);
         
Draws an image from the gievn pixels scaled to the specified scale using the (x, y) coordiantes from the Rectangle for the top left of the image.

.. note::
  
  On top of using the (x, y) coordiantes for the top left, the passed Rectangle should also have the width and height of the *original* 
  image size. If you are using ``waphics_image_load`` this information can be found in the generated header file.
  
.. code-block:: c

    void waphics_draw_image_alpha(Surface display, Rectangle rect,
          uint32_t scale, uint32_t *pixels, uint32_t alpha);
          
 Identical to ``waphics_draw_image`` execept for blending each pixel with the specified alpha value.

