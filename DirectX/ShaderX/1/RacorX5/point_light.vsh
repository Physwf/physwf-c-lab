;specular light
#include "const.h"

vs.1.1
;transpose and transform to clip space
mul r0, v0.x, c[CLIP_MATRIX]
mad r0, v0.y, c[CLIP_MATRIX_1], r0
mad r0, v0.z, c[CLIP_MATRIX_2], r0
add oPos, c[CLIP_MATRIX_3], r0
;output texture coords
mov oT0, v7
;transform normal
dp3 r1.x, v3, c[INVERSE_WORLD_MATRIX]
dp3 r1.y, v3, c[INVERSE_WORLD_MATRIX_1]
dp3 r1.z, v3, c[INVERSE_WORLD_MATRIX_2]
;renormalize it
dp3 r1.w, r1, r1
rsq r1.w, r1.w
mul r1, r1, r1.w

;transform vertices to world space
mul r7, v0.x, c[WORLD_MATRIX]
mad r7, v0.y, c[WORLD_MATRIX_1], r7
mad r7, v0.z, c[WORLD_MATRIX_2], r7
add r7, c[WORLD_MATRIX_3], r7

;calculate vector from light position to vertex position L
add r10.xyz, c[LIGHT_POSITION], -r7.xyz
dp3 r10.w, r10, r10
rsq r11.w, r10.w
mul r11, r10, r11.w

dp3 r0.x, r1, r11 ;N dot L

dst r4, r10.w, r11.w

dp3 r7.x, r4, c[LIGHT_ATTENUATION]
rcp r7.x, r7.x
;calculate half vector H = L + V
add r2, c[EYE_VECTOR], r11 ; L + V
;normalize H
dp3 r2.w, r2, r2
rsq r2.w, r2.w
mul r2, r2, r2.w
;N dot H
dp3 r0.y, r1, r2
;lit
mov r0.w, c[SPEC_POWER].y
lit r4, r0

mul r4, r4, r7.xxxx

mul oD0, c[DIFFUSE_COLOR], r4.y
mul oD1, c[SPEC_COLOR], r4.z