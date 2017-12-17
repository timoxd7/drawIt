#ifndef drawIt_h
#define drawIt_h

#include "Arduino.h"

class drawIt
{
  public:
  
  class slider{
    public:
      slider(TFT_ILI9341 display, int x_origin, int y_origin, int x_length, int y_length, float value, bool touch);

      void changeOrigin(int x_origin, int y_origin);
      void changeLength(int x_length, int y_length);

      void setValue(float value);
      void value(float value);

      float getValue();
      float value();

      void setTouch(bool activated);
      void touch(bool activated);

      bool getTouch();
      bool touch();

      void touched(int x, int y);

      void draw();
      
    private:
      TFT_ILI9341 _display;
      int _x_origin, _y_origin;
      int _x_length, _y_length;
      float _value;
      bool _touch;
  };


  class button{
    public:

    private:
    
  };
};

#endif
