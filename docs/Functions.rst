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

.. code-block:: c

  void waphics_fill_screen(Screen screen, uint32_t color);

Fills the specified Screen with the specified color

.. note::
  
  Colors should be in the following format:
  0xAABBGGRR


.. code-block:: c
