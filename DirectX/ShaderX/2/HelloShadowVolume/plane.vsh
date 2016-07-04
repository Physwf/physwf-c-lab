vs.1.1
;m4x4 oPos, v0, c0
mul r0, v0.x, c0
mad r0, v0.y, c1, r0
mad r0, v0.z, c2, r0
add oPos, c3, r0