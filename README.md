qsplat
======

QSplat implementation for ACG

Controls:
w - move camera up
s - move camera down
a - move camera left
d - move camera right
r - zoom in
f - zoom out
z - recurse more in hierachy
x - recurse less in hierachy
c - toggle normal cone backface culling (normal cone mode uses normal cones for
    backface culling, whereas conventional mode only tests the normal, not the
    cone - this does not work properly for the highest resolution
    dragon_vrip.ply, but works for other resolutions of the dragon, and the 
    bunny)

Note: binary read in of ply files was not implemented, so lucy cannot be loaded
Note II: frustum culling was not implemented
Note III: Frame rate does not display correctly 
