#include "Arduino.h"
#include "RGBLED.h"

RGBLED::RGBLED(int redpin, int greenpin, int bluepin) {
  _pins[0] = redpin;
  _pins[1] = greenpin;
  _pins[2] = bluepin;
  pinMode(_pins[0], OUTPUT);
  pinMode(_pins[1], OUTPUT);
  pinMode(_pins[2], OUTPUT);
  _clr[0] = 255;
  _clr[1] = 255;
  _clr[2] = 255;
  pclr[0] = 0;
  pclr[1] = 0;
  pclr[2] = 0;
}

bool RGBLED::stepto(int clr[], int cycles) {
	if (_clr[0] == clr[0] && _clr[1] == clr[1] && _clr[2] == clr[2]) {
		pclr[0] = _clr[0];
		pclr[1] = _clr[1];
		pclr[2] = _clr[2];
		return true;
	}
	double rstep = ((pclr[0]-clr[0])/((double)cycles));
	double gstep = ((pclr[1]-clr[1])/((double)cycles));
	double bstep = ((pclr[2]-clr[2])/((double)cycles));
	if (_clr[0] - rstep < clr[0] && _clr[0] > clr[0] || _clr[0] - rstep > clr[0] && _clr[0] < clr[0] || _clr[0] == clr[0]) {
		_clr[0] = clr[0];
	}
	else {
		_clr[0] -= rstep;
	}
	if (_clr[1] - gstep < clr[1] && _clr[1] > clr[1] || _clr[1] - gstep > clr[1] && _clr[1] < clr[1] || _clr[1] == clr[1]) {
		_clr[1] = clr[1];
	}
	else {
		_clr[1] -= gstep;
	}
	if (_clr[2] - bstep < clr[2] && _clr[2] > clr[2] || _clr[2] - bstep > clr[2] && _clr[2] < clr[2] || _clr[2] == clr[2]) {
		_clr[2] = clr[2];
	}
	else {
		_clr[2] -= bstep;
	}
	return false;
}

void RGBLED::reset() {
	_clr[0] = 255;
	_clr[1] = 255;
	_clr[2] = 255;
	pclr[0] = 0;
	pclr[1] = 0;
	pclr[2] = 0;
}

void RGBLED::output() {
	chkallranges();
	analogWrite(_pins[0], (int) _clr[0]);
	analogWrite(_pins[1], (int) _clr[1]);
	analogWrite(_pins[2], (int) _clr[2]);
}

void RGBLED::output(int red, int green, int blue){
	_clr[0] = (double) red;
	_clr[1] = (double) green;
	_clr[2] = (double) blue;
	chkallranges();
	analogWrite(_pins[0], (int) _clr[0]);
	analogWrite(_pins[1], (int) _clr[1]);
	analogWrite(_pins[2], (int) _clr[2]);
}

void RGBLED::setColors(int red, int green, int blue) {
	_clr[0] = (double) red;
	_clr[1] = (double) green;
	_clr[2] = (double) blue;
}

void RGBLED::setColors(double red, double green, double blue) {
	_clr[0] = red;
	_clr[1] = green;
	_clr[2] = blue;
}

void RGBLED::setColors(int *clr) {
	_clr[0] = (double) clr[0];
	_clr[1] = (double) clr[1];
	_clr[2] = (double) clr[2];
}

void RGBLED::chkallranges(){
	chkranges(&_clr[0]);
	chkranges(&_clr[1]);
	chkranges(&_clr[2]);
}

void RGBLED::chkranges(double *in) {
	if (*in > 255) {
		*in = 255;
	}
	else if (*in < 0){
		*in = 0;
	}
}