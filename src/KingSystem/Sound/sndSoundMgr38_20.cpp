#include "KingSystem/Sound/sndSound.h"
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/Utils/InitTimeInfo.h"
#include "Game/Actor/actEnvSeEmitPoint.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Terrain/teraSystem.h"
#include <prim/seadScopedLock.h>
#include <aal/aalSpeakerBalanceUnifier.h>
#include "Game/gameUnkRttiPlaceholders.h"

// Address placeholder for the original kind-name text lookup; its enum type is not recovered.
const char* sub_7101029E34(u32 kind);

namespace ksys::snd {

// Unk_SoundMgr38_20 is a TU of its own in the original (0x7101029864..0x7101029fe0, no statics):
// Unk_SoundMgr38 calls its small functions instead of inlining them.

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

void Unk_SoundMgr38_20::sub_71010299AC() {
    auto lock = sead::makeScopedLock(mCS);
    if (_8[0].size() == 0)
        return;
    sub_7101029D3C(&_8[0]);
    s32 index = 0;
    for (auto& point : _8[0]) {
        if (index <= 3)
            point.sub_7101029620(false);
        else
            point.sub_7101029620(true);
        ++index;
    }
    for (auto& point : _8[0])
        point.sub_71010296B0();
}

void Unk_SoundMgr38_20::sub_7101029AA0() {
    auto lock = sead::makeScopedLock(mCS);
    if (_8[1].size() == 0)
        return;
    sub_7101029D3C(&_8[1]);
    s32 index = 0;
    for (auto& point : _8[1]) {
        if (index <= 5)
            point.sub_7101029620(false);
        else
            point.sub_7101029620(true);
        ++index;
    }
    for (auto& point : _8[1])
        point.sub_71010296B0();
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

// NON_MATCHING: the existing list API uses a different offset-negation instruction and address-load order.
void Unk_SoundMgr38_20::sub_7101029D3C(sead::OffsetList<uking::act::EnvSeEmitPoint>* points) {
    for (auto& point : *points)
        point.sub_7101029658();
    // The native insertion comparison includes unordered float values.
    points->insertionSort([](const uking::act::EnvSeEmitPoint* a,
                             const uking::act::EnvSeEmitPoint* b) {
        return !(a->_840 <= b->_840);
    });
}

}  // namespace ksys::snd
