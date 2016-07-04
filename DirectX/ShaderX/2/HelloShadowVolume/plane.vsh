vs.1.1
;m4x4 oPos, v0, c0
;mul r0, v0.x, c0
;mad r0, v0.y, c1, r0
;mad r0, v0.z, c2, r0
;add oPos, c3, r0

dp4 oPos.x, v0, c0
dp4 oPos.y, v0, c1
dp4 oPos.z, v0, c2
dp4 oPos.w, v0, c3