#include "gd.h"
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

inline int imod(int i, int j) {
  return (i % j) < 0? (i % j) + (j < 0? -j : j) : i % j;
}

void mandelbrot(double re, double im, int N, vector<int>& ret) {
  double x = 0.0, y = 0.0;
  double x1 = 0.0, y1 = 0.0;
  for(int n = 1; n != N; ++n) {
	x1 = x*x-y*y+re;
	y1 = 2.0*x*y+im;
	if(x1*x1+y1*y1 > 4.0) {
	  ret.push_back(n);
	  ret.push_back(static_cast<int>(x1*1000));
	  ret.push_back(static_cast<int>(y1*1000));
	  return;
	}
	x = x1;
	y = y1;
  }
  ret.push_back(0);
}
  
int main() {
  int IW = 400;
  int IH = 400;
  int x0 = IW/2;
  int y0 = IH/2;
  int NMAX = 500;
  double amp = 0.01;
  vector<int> nxy(3);
  const char *outfile = "mandelbrot.png";
  gdImagePtr im = gdImageCreate(IW, IH);
  for(int w = -IW/2; w <= IW/2; ++w) {
	for(int h = -IH/2; h <= IH/2; ++h) {
	  nxy.clear();
	  mandelbrot(w*amp, h*amp, NMAX, nxy);
	  int color = nxy.at(0) == 0?
		gdImageColorResolve(im, 0, 0, 0):
		gdImageColorResolve(im,	imod(nxy.at(0), 255), imod(nxy.at(1), 255), imod(nxy.at(2), 255));
	  gdImageSetPixel(im, x0+w, y0+h, color);
	}
  }
  FILE *out = fopen(outfile, "wb");
  if(out == NULL)
	return 1;
  cout << "output: " << outfile << endl;
  gdImagePng(im, out);
  fclose(out);
  gdImageDestroy(im);
  return 0;
}
