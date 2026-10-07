#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/Utils/InitTimeInfo.h"
#include "Game/Actor/actEnvSeEmitPoint.h"
#include <prim/seadScopedLock.h>

// Address placeholder for the original kind-name text lookup; its enum type is not recovered.
const char* sub_7101029E34(u32 kind);

namespace ksys::snd {

// The TU's static initialiser is 0x710103ae20 (`_GLOBAL__sub_I_sndSoundMgr38.cpp`).
static util::InitTimeInfoEx sInitTimeInfo;

// NON_MATCHING: the compiler combines the adjacent flag and float initialization stores.
Unk_SoundMgr38_20::Unk_SoundMgr38_20() = default;

Unk_SoundMgr38_20::~Unk_SoundMgr38_20() {
    _8[0].clear();
    _8[1].clear();
}

void Unk_SoundMgr38_20::sub_7101029958(sead::Heap* heap) {
    _7a[0] = false;
    _7a[1] = false;
    _8[0].initOffset(0x850);
    _8[1].initOffset(0x850);
}

void Unk_SoundMgr38_20::sub_7101029970() {
    if (_78) {
        sub_71010299AC();
        sub_7101029AA0();
    }
}

void Unk_SoundMgr38_20::sub_7101029B94() { _78 = true; }
void Unk_SoundMgr38_20::sub_7101029BA0() { _78 = false; }
void Unk_SoundMgr38_20::sub_7101029BA8() { _78 = false; }

bool Unk_SoundMgr38_20::sub_7101029BB0(uking::act::EnvSeEmitPoint* point) {
    if (!point)
        return false;
    u32 kind = 0;
    if (point->getName().findIndex(sub_7101029E34(0)) == -1) {
        kind = 1;
        if (point->getName().findIndex(sub_7101029E34(1)) == -1)
            return false;
    }
    point->_83c = kind;
    point->_84d = _7a[kind];
    auto lock = sead::makeScopedLock(mCS);
    _8[kind].pushBack(point);
    return true;
}

void Unk_SoundMgr38_20::sub_7101029C98(uking::act::EnvSeEmitPoint* point) {
    if (!point)
        return;
    const s32 kind = point->_83c;
    if (kind < 0 || kind >= 2)
        return;
    auto lock = sead::makeScopedLock(mCS);
    if (_8[kind].indexOf(point) >= 0) {
        point->_84d = 0;
        _8[kind].erase(point);
    }
}

Unk_SoundMgr38_28* Unk_SoundMgr38::sub_710102C104() const {
    return _28;
}

// NON_MATCHING: only the schedule (the original loads both vectors up front and keeps the six results in
// registers before the stores).
void Unk_SoundMgr38_28::sub_7101037ED8(const sead::Vector3f* pos, const sead::Vector3f* size) {
    const sead::Vector3f half = *size * 0.5f;
    mBoxMin = *pos - half;
    mBoxMax = half + *pos;
    mBoxCenter = *pos;
    mBoxSize = *size;
}

void Unk_SoundMgr38_28::sub_7101037F5C(u8 value) {
    _344 = value;
}

void Unk_SoundMgr38_28::sub_7101037F64(bool enabled) {
    _328 = enabled;
    if (!enabled) {
        _3c8 = nullptr;
        _3c0 = nullptr;
    }
}

void Unk_SoundMgr38_28::sub_7101037F7C(bool value) {
    _39c = value;
}

}  // namespace ksys::snd
