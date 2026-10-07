#include "Game/AI/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

sead::Vector3f sUnk_71025c8cf8(0, 0, 900);
const f32 sUnk_7102450fa0 = 50.0f;
const sead::SafeArray<const char*, 3> sUnk_7102450f80 = {
    {"Priest_Boss_FireArrow", "Priest_Boss_IceArrow", "Priest_Boss_ElectricArrow"}};
const char* const sUnk_7102450f98 = "Grave";

s32 Unk_7102450fa8::sub_7100719FCC() const {
    return _88 ? _88->_ac : -1;
}

// NON_MATCHING: the original calls m6 non-tail and round-trips the result through the stack (the return type is likely a
// SEAD_ENUM-style wrapper)
s32 Unk_7102450fa8::sub_7100719FE4(s32 idx) {
    return _88 ? _88->m6(idx) : 3;
}

bool Unk_7102450fa8::sub_710071A020(sead::Vector3f* out, s32 idx) {
    if (!_88)
        return false;
    _88->m7(out, idx);
    return true;
}

s32 Unk_7102450fa8::sub_710071A048(s32 idx) {
    return _88 ? *_88->_b8[idx - 2] : -1;
}

bool Unk_7102450fa8::sub_7100719978(s32 idx) const {
    if (idx == 2 || u32(idx - 2) > 8)
        return false;
    return _80 >> idx & 1;
}

bool Unk_7102450fa8::sub_71007194CC(ksys::act::ActorConstDataAccess* accessor) {
    return ksys::act::acquireActor(&_18, accessor);
}

bool Unk_7102450fa8::sub_71007194D4(int idx, ksys::act::ActorConstDataAccess* accessor) {
    if (idx < 0 || idx >= _8.size())
        return false;

    ksys::act::acquireActor(&_8[idx]._e0, accessor);
    return accessor->hasProc();
}

// NON_MATCHING: loop exit compare (original: cmp #32 / b.le; ours: cmp #33 / b.lt)
int Unk_7102450fa8::sub_7100719534(ksys::act::BaseProc* proc) {
    for (int i = 0; i <= 32; ++i) {
        if (_8[i]._e0.hasProcById(proc))
            return i;
    }
    return -1;
}

// NON_MATCHING: loop exit compare (original: cmp #32 / b.le; ours: cmp #33 / b.lt)
int Unk_7102450fa8::sub_71007195B0(const ksys::act::BaseProcLink& link) {
    for (int i = 0; i <= 32; ++i) {
        if (_8[i]._e0 == link)
            return i;
    }
    return -1;
}

bool Unk_7102450fa8::sub_710071A22C() {
    if (_3c8 <= 0.0f)
        return false;
    return _350.value <= sead::Mathf::epsilon();
}

bool Unk_7102450fa8::sub_710071A2D0() {
    return _35c.value <= sead::Mathf::epsilon();
}
