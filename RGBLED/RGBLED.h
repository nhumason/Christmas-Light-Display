#ifndef RGBLED_h
#define RGBLED_h

#include "arduino.h"

class RGBLED
{
  public:
    RGBLED(int redpin, int greenpin, int bluepin);
	bool stepto(int clr[], int cycles);
    void output();
	void output(int red, int green, int blue);
	void setColors(int,int,int);
	void setColors(double red, double green, double blue);
	void setColors(int *clr);
    int Red() const {return (int) _clr[0]; };
    int Green() const {return (int) _clr[1]; };
    int Blue() const {return (int) _clr[2];};
    void Red(int red) {_clr[0] = (double) red;};
    void Green(int green) {_clr[1] = (double) green;};
    void Blue(int blue) {_clr[2] = (double) blue;};
	void reset();
  private:
	void chkranges(double *in);
	void chkallranges();
    int _pins [3];
    double _clr [3];
	double pclr [3];
};

#endif
