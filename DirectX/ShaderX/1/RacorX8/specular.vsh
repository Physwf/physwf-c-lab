#include "const.h"
;diff light
;v0 position
;v3 normal
;v7 texture 
;v8 tangent 

vs.1.1
;transform to clip space
m4x4 oPos, v0, c8

;transform position to world space
m4x4 r2, v0, c0
add r2, -r2, c24

;compute and normalize eye vector
dp3 r11.x, r2, r2
rsq r11.xyz, r11.x
mul r2.xyz, r2.xyz, r11.xyz

;compute half vector
add r2.xyz, r2.xyz, -c12

;compute U,V,W
m3x3 r5, v8, c0 ;U
m3x3 r7, v3, c0 ;W
;V = U x W
mul r0, r5.zxyw, -r7.yzxw
mad r6, r5.yzxw, -r7.zxyw, -r0 ;V

;transform half vector to texture space
dp3 r8.x, r5, r2
dp3 r8.y, r6, r2
dp3 r8.z, r7, r2

mad oD1.xyz, r8.xyz, c33, c33

;output texture coords
mov oT0.xy, v7.xy
mov oT1.xyz, r8
mov oT2.xyz, r8
mov oT3.xy, v7.xy