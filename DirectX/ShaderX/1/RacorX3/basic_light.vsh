;basic light
#include "const.h"

vs.1.1
;transpose and transform to clip space
mul r0, v0.x, c[CLIP_MATRIX]
mad r0, v0.y, c[CLIP_MATRIX_1], r0
mad r0, v0.z, c[CLIP_MATRIX_2], r0
add oPos, c[CLIP_MATRIX_3], r0
;transform normal
dp3 r1.x, v3, c[INVERSE_WORLD_MATRIX]
dp3 r1.y, v3, c[INVERSE_WORLD_MATRIX_1]
dp3 r1.z, v3, c[INVERSE_WORLD_MATRIX_2]
;renormalize it
dp3 r1.w, r1, r1
rsq r1.w, r1.w
mul r1, r1, r1.w
;N dot L
;we need L verctor towards the light, thus negate sign
dp3 r0, r1, -c[LIGHT_POSITION]
mul r0, r0, c[LIGHT_COLOR]
mul oD0, r0, c[DIFFUSE_COLOR]