#include "const.h"
;diff light
;v0 position
;v3 normal
;v7 texture 
;v8 tangent 

vs.1.1
;transpose and transform to clip space

m4x4 oPos, v0, c8

;output texture coords
;transform normal

m3x3 r5, v3, c0 ;U
m3x3 r7, v8, c0 ;W

;V
mul r0, r5.zxyw, -r7.yzxw
mad r6, r5.yzxw, -r7.zxyw, -r0

;transform light to texture space
dp3 r8.x, r5, -c12
dp3 r8.y, r6, -c12
dp3 r8.z, r7, -c12

mad oD0.xyz, r8.xyz, c33, c33

mov oT0.xy, v7.xy
mov oT1.xy, v7.xy