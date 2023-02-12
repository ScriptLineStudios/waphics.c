Functions
================================

.. code-block:: c

  Rectangle waphics_rectangle_new(int x, int y, int width, int height);

Returns a new Rectangle with the specifed x, y, width and height.

.. code-block:: c

  Circle waphics_circle_new(int x, int y, int radius);

Returns a new Circle with the specified x, y and radius.

.. code-block:: c

  Screen waphics_screen_new(uint32_t *pixels, unsigned int width, unsigned int height);

Returns a new Screen.

.. note::

  All functions which return a new instance of a strcture have corrosponding macros:
  
  .. code-block:: c

    #define RECT(x, y, w, h) waphics_rectangle_new(x, y, w, h)
    #define CIRCLE(x, y, r) waphics_circle_new(x, y, r)
    #define SCREEN(pixels, w, h) waphics_screen_new(pixels, w, h)

.. code-block:: c

  void waphics_fill_screen(Screen screen, uint32_t color);

Fills the specified Screen with the specified color

.. note::
  
  Colors should be in the following format:
  0xAABBGGRR
  
  Alternatily the RGBA or RGB macros can be used:
  
  .. code-block:: c
  
    #define RGBA(r, g, b, a) ((((r)&0xFF)<<(8*0)) | (((g)&0xFF)<<(8*1)) | (((b)&0xFF)<<(8*2)) | (((a)&0xFF)<<(8*3)))
    #define RGB(r, g, b) ((((r)&0xFF)<<(8*0)) | (((g)&0xFF)<<(8*1)) | (((b)&0xFF)<<(8*2)) | (((255)&0xFF)<<(8*3)))

.. code-block:: c

  void waphics_draw_rect(Screen screen, Rectangle rect, uint32_t color);

Draws a rectangle with the given color 

.. code-block:: c

  void waphics_draw_line(Screen screen, int x1, int y1, int x2, int y2, int color);

Draws a line from point (x1, y1) to (x2, y2)

.. code-block:: c

  void waphics_draw_circle(Screen screen, Circle circle, uint32_t color);

Draws a circle from the given Circle instance.

.. code-block:: c

  void waphics_draw_triangle(Screen screen, int _x1, int _y1, 
                                    int _x2, int _y2, 
                                    int _x3, int _y3, uint32_t color1, uint32_t color2, uint32_t color3);

Draws a triangle with points (x1, y1); (x2, y2); (x3, y3) with corrosponding colors at the points.

.. code-block:: c

  void waphics_draw_image(Screen screen, Rectangle rect,
          uint32_t scale, uint32_t *pixels);
         
Draws an image from the gievn pixels scaled to the specified scale using the (x, y) coordiantes from the Rectangle for the top left of the image.

.. note::
  
  On top of using the (x, y) coordiantes for the top left, the passed Rectangle should also have the width and height of the *original* 
  image size. If you are using ``waphics_image_load`` this information can be found in the generated header file.
  
.. code-block:: c

    void waphics_draw_image_alpha(Screen screen, Rectangle rect,
          uint32_t scale, uint32_t *pixels, uint32_t alpha);
          
 Identical to ``waphics_draw_image`` execept for blending each pixel with the specified alpha value.

