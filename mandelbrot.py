from PIL import Image, ImageDraw 
from cmath import *

outfile = 'mandelbrot.jpg'

IW = 400
IH = 400
x0 = IW/2
y0 = IH/2

NMAX = 500
amp = 0.01

def mandelbrot(a, b):
  x = y = x1 = y1 = 0.0
  for n in range(1, NMAX):
    x1 = x*x-y*y+a
    y1 = 2.0*x*y+b
    if x1*x1+y1*y1 > 4.0:
      return n,x1,y1
    x = x1
    y = y1
  return 0,0,0

img = Image.new('RGB', (IW, IH), (255,255,255))
drw = ImageDraw.Draw(img)

for w in range(-IW/2, IW/2+1):
  for h in range(-IH/2, IH/2+1):
    n,x,y = mandelbrot(w*amp, h*amp)
    if n == 0:
      drw.point((x0+w, y0+h), fill=(0,0,0))
    else:
      drw.point((x0+w, y0+h), fill=(n%255,int(x*100)*n%255,int(y*100)*n%255))

with open(outfile, 'wb') as out: img.save(out)
#img.show()
