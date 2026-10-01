#include "Game/AI/aiUnkDamageCallbacks.h"

void Unk_71024518c8::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a4 == 3) {
        *a5 = -1;
        *a1 = 0;
    }
}

void Unk_7102451938::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if ((*a5 == 7 || *a5 == 8) && *a1 == 0)
        *a1 = _24;
}

void Unk_7102451970::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    switch (*a5) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 15:
    case 17:
    case 21:
        *a5 = 22;
        break;
    default:
        break;
    }
}

void Unk_71024519e0::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a5 != -1)
        *a5 = 1;
}

void Unk_7102451a88::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a5 == 32) {
        *a5 = -1;
        *a4 = -1;
    }
}

void Unk_7102451ac0::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a5 == 20) {
        *a5 = -1;
        *a1 = 0;
        *a4 = -1;
    }
}

void Unk_7102451bd8::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a5 != -1 && *a5 <= 21)
        *a5 = 2;
}

void Unk_7102451c10::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a4 == 15) {
        *a4 = -1;
        *a5 = -1;
        *a1 = 0;
    }
}

void Unk_7102451c98::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a5 >= 3)
        *a5 = 2;
}

void Unk_7102451d78::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a5 != -1 && *a5 < _24)
        *a5 = 2;
}
