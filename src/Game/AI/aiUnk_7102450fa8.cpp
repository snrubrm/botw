#include "Game/AI/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

sead::Vector3f sUnk_71025c8cf8(0, 0, 900);
const f32 sUnk_7102450fa0 = 50.0f;
const sead::SafeArray<const char*, 3> sUnk_7102450f80 = {
    {"Priest_Boss_FireArrow", "Priest_Boss_IceArrow", "Priest_Boss_ElectricArrow"}};
const char* const sUnk_7102450f98 = "Grave";

s32 Unk_7102450fa8::sub_7100719FCC() const {
    return _88 ? _88->_ac : -1;
}

// The result goes through a Phase temporary (the return value is stored to the stack and reloaded).
s32 Unk_7102450fa8::sub_7100719FE4(s32 idx) {
    if (_88) {
        const Phase phase = _88->m6(idx);
        return phase;
    }
    return 3;
}

s32 Unk_7102450fa8::sub_7100719FA4() {
    if (_88) {
        const Phase phase = _88->_a8;
        return phase;
    }
    return 0;
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

bool Unk_7102450fa8::sub_710071962C(sead::Vector3f* out) {
    out->set(sUnk_71025c8cf8);
    return true;
}

void Unk_7102450fa8::sub_71007199A8() {
    _80 = 0;
    _68 = 0;
    _70 = 0;
    _50 = 0;
    _58 = 0;
    _60 = 0;
}

s32 Unk_7102450fa8::sub_7100719F70() {
    if (_88) {
        const Phase phase = _88->m4();
        return phase;
    }
    return 0;
}

void Unk_7102450fa8::sub_710071A1C0(u32 a, u32 b) {
    _3f0.pushBack({a, b});
}

bool Unk_7102450fa8::sub_710071A200() const {
    if (_348 > 0) {
        if (_34c >= _348)
            return true;
    }
    return false;
}

void Unk_7102450fa8::sub_710071A258() {
    ksys::act::ActorConstDataAccess accessor;
    if (_8.size() > 1) {
        ksys::act::acquireActor(&_8[1]._e0, &accessor);
        if (accessor.hasProc() && !accessor.sub_7100D10FB8())
            _350.update();
    }
    _3e0.update();
}

void Unk_7102450fa8::sub_710071A2E8() {
    if (sub_710071A22C()) {
        _35c.update();
        return;
    }

    ksys::act::ActorConstDataAccess accessor;
    if (_8.size() > 1) {
        ksys::act::acquireActor(&_8[1]._e0, &accessor);
        if (accessor.hasProc() && !accessor.sub_7100D10FB8())
            _35c.update();
    }
}

// NON_MATCHING: the original loads both procs before ~ActorConstDataAccess, compares after it and branches to the
// constant 1 (ours: cset after the destructor).
bool Unk_7102450fa8::sub_710071A38C(const ksys::act::ActorConstDataAccess* accessor) {
    if (_3e0.value <= sead::Mathf::epsilon() || !_3d0.hasProc())
        return false;

    ksys::act::ActorConstDataAccess other;
    ksys::act::acquireActor(&_3d0, &other);
    return other.getProc() == accessor->getProc();
}

bool Unk_7102450fa8::sub_710071A22C() {
    if (_3c8 <= 0.0f)
        return false;
    return _350.value <= sead::Mathf::epsilon();
}

bool Unk_7102450fa8::sub_710071A2D0() {
    return _35c.value <= sead::Mathf::epsilon();
}

void Unk_7102450fa8::sub_71007190CC(const ksys::MesTransceiverId& dest) {
    if (auto* actor = sead::DynamicCast<ksys::act::Actor>(_18.getProc(nullptr)))
        actor->sendMessage(dest, ksys::MessageType(0x80000d9), this, true);
}

void Unk_7102450fa8::sub_7100719ED0() {
    sead::ScopedLock<sead::JobQueueLock> lock(&_9c);
    _a0.clear();
}
