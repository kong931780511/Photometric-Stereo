# Photometric-Stereo
Photometric stereo is a technique to recover local surface orientations
## Assignment Generalization
Its mathmatical principle can be easily found on Internet. This assignment is going to use multiple images of an object captured under different directional illuminations and the same viewpoint to calibrate the illumination direction, estimate the surface normal direction at every pixel.<br>
## Calculating Process
* Using class `PFMAcess` provided by Dr. Qin to read the data in form of PBM
* Read 21 images and transfer their data to Mat format (function `Readstring` & function `Transfer`)<br>
* Recorded every pixel value and formed their RGB value as Intensity matrix (function `Calpix`)<br>
* Calculated light intensity of ever image through the brightest point on the Lambertian sphere and take its albedo as 1 (function `CalLam`)<br>
* Calculated the illumination direction of ever image through the brightest point of the right metal sphere and its radium (function `CalBPoint` & function `CalCenter` & function `CalL`)<br>
 >>>>>L=2(N.R)N-R<br>
 >>>>> Nx=BPx-Cx<br>
 >>>>> Ny=BPy-Cy<br>
 >>>>>  Nz=sqrt(R^2-Nx^2-Ny^2)<br>
 >>>>> [ Taken R as (0,0,1) ]<br>
* Calculated the albedo and the surface normal for every point on the object(function `CalG`)<br>
 >>>>>>G= invert ( tranverse(L)*L)*tranverse(L)*I<br>
 >>>>>kd = ||G||<br>
 >>>>>N  = G/kd<br>

## Result
#### (RGB, albedo and re-rendered pictures are arranged from left to right)
### apple
![](https://github.com/kong931780511/Photometric-Stereo/raw/master/data/apple_rgb.png)
![](https://github.com/kong931780511/Photometric-Stereo/raw/master/data/apple_albedo.png) 
![](https://github.com/kong931780511/Photometric-Stereo/raw/master/data/apple_render.png) 
### elephant
<img src="https://github.com/kong931780511/Photometric-Stereo/raw/master/data/elephant_rgb.png" width="30%" height="30%"><img src="https://github.com/kong931780511/Photometric-Stereo/raw/master/data/elephant_albedo.png" width="30%" height="30%"><img src="https://github.com/kong931780511/Photometric-Stereo/raw/master/data/elephant_render.png" width="30%" height="30%">
### pear
![](https://github.com/kong931780511/Photometric-Stereo/raw/master/data/pear_rgb.png) 
![](https://github.com/kong931780511/Photometric-Stereo/raw/master/data/pear_albedo.png) 
![](https://github.com/kong931780511/Photometric-Stereo/raw/master/data/pear_render.png) 
# How to use
* Be sure to install OpenCV on your computer
* main class is included in `PRECal.h` and `PRECal.cpp`
* Run the main function in `pp.cpp`
* Enter the number of images you use
* Enter the object's name ('apple','elephant'or'pear)
* Wait for the reslut<br>
  If you still have questions, please feel free to contact me. `kongosu325@outlook.com`
