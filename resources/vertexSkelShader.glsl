#version 400

uniform mat2x4 qBone[4];

in vec3 vp;
in vec3 vn;
in uint joint[4];
in float weight[4];

void main() {
  gl_Position = vec4(vp, 1.0);
}

bˆ = w 1 qˆ j 1 + . . . + w n qˆ j n
// denote the non-dual part of bˆ as b0 and the dual one as bε
c = b /∥b ∥ 000
cε =bε/∥b0∥
// denote the components of c0 as w0,x0,y0,z0 // denote the components of cε as wε,xε,yε,zε t0 =2(−wεx0+xεw0−yεz0+zεy0)
t1 =2(−wεy0+xεz0+yεw0−zεx0)
t2 = 2(−wεz0 −xεy0 +yεx0 +zεw0)
⎛1−2y2−2z2 2xy−2wz 2xz+2wy t⎞ ⎝00000000000⎠
2x0y0 +2w0z0 1−2x20 −2z20 2y0z0 −2w0x0 t1 2x0z0 −2w0y0 2y0z0 +2w0x0 1−2x20 −2y20 t2
v = Mv // where v has form v = (v0,v1,v2,1)
v′n = Mvn // where vn has form vn = (vn,0,vn,1,vn,2,0)