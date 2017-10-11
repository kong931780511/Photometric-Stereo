# Photometric-Stereo
Photometric stereo is a technique to recover local surface orientations
## Assignment Generalization
Its mathmatical principle can be easily found on Internet. This assignment is going to use multiple images of an object captured under different directional illuminations and the same viewpoint to calibrate the illumination direction, estimate the surface normal direction at every pixel.<br>
## Calculating Process
* Read 21 images and transfer their data to Mat format (function 'Readstring' & function 'Transfer')<br>
* Recorded every pixel value and formed their RGB value as Intensity matrix (function 'Calpix')<br>
* Calculated light intensity of ever image through the brightest point on the Lambertian sphere and take its albedo as 1 (function 'CalLam')<br>
* Calculated the illumination direction of ever image through the brightest point of the right metal sphere and its radium (function 'CalBPoint' & function 'CalCenter' & function 'CalL')<br>
 >>>>>L=2(N.R)N-R<br>
 >>>>> Nx=BPx-Cx<br>
 >>>>> Ny=BPy-Cy<br>
 >>>>>  Nz=sqrt(R^2-Nx^2-Ny^2)<br>
 >>>>> [ Taken R as (0,0,1) ]<br>
* Calculated the albedo and the surface normal for every point on the object(function 'CalG')<br>
 >>>>>>G= invert ( tranverse(L)*L)*tranverse(L)*I<br>
 >>>>>kd = ||G||<br>
 >>>>>N  = G/kd<br>

## Result
(RGB, albedo and re-rendered pictures are arranged from left to right)
