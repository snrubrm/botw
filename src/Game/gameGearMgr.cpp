#include "Game/gameGearMgr.h"
#include <math/seadMathCalcCommon.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking {

bool GearMgr::sub_71006690B8(ksys::act::BaseProc* proc) {
    if (!proc)
        return false;

    mCS.lock();
    for (size_t i = 0; i < 0x80; ++i) {
        auto& link = mEntries[i].mLink;
        if (link.hasProc() && link.hasProcById(proc)) {
            mCS.unlock();
            return true;
        }
    }
    mCS.unlock();
    return false;
}

// NON_MATCHING: regalloc only (the original keeps `this` in x19 and `&mCS` in x20).
void GearMgr::sub_71006692F0(ksys::act::Actor* actor, bool join_system_group) {
    if (!actor)
        return;

    if (sub_71006690B8(actor))
        return;

    mCS.lock();
    for (size_t i = 0; i < 0x80; ++i) {
        auto& entry = mEntries[i];
        if (!entry.mLink.hasProc()) {
            entry.mLink.acquire(actor, false);
            entry._10 = join_system_group;
            if (join_system_group) {
                if (auto* physics = actor->getPhysics())
                    physics->sub_7100FBDFA4(_1050);
            }
            break;
        }
    }
    mCS.unlock();
}

void GearMgr::sub_71006694B4(ksys::act::Actor* actor) {
    if (!actor)
        return;

    mCS.lock();
    for (size_t i = 0; i < 0x80; ++i) {
        auto& entry = mEntries[i];
        if (entry.mLink.hasProc() && entry.mLink.hasProcById(actor)) {
            if (entry._10) {
                if (auto* physics = actor->getPhysics()) {
                    physics->sub_7100FBDFA4(physics->get178(0));
                    physics->sub_7100FBDFA4(physics->get178(1));
                }
            }
            entry.mLink.reset();
            break;
        }
    }
    mCS.unlock();
}

void GearMgr::sub_710066956C(ksys::act::BaseProc* proc, bool join_system_group) {
    if (!proc)
        return;

    mCS.lock();
    _1030.mLink.acquire(proc, false);
    _1030._10 = join_system_group;
    mCS.unlock();
}

void GearMgr::sub_71006695DC(ksys::act::BaseProc* proc) {
    mCS.lock();
    if (_1030.mLink.hasProc() && _1030.mLink.hasProcById(proc))
        _1030.mLink.reset();
    mCS.unlock();
}

void GearMgr::sub_71006698B0(bool on) {
    mCS.lock();
    if (on)
        _10a8[_28] |= 4;
    else
        _10a8[_28] &= ~4u;
    mCS.unlock();
}

void GearMgr::sub_7100669AF8(f32 value) {
    mCS.lock();
    _10c4 = value;
    mCS.unlock();
}

bool GearMgr::sub_7100669B48() {
    _10b0[_2c] |= 2;
    return (_10b0[_2c ^ 1] >> 1) & 1;
}

// NON_MATCHING: block layout (the original branches to the end on `value < 0`) and the flag word is
// loaded whole (`ldr` + `tbnz`) instead of as a byte.
bool GearMgr::sub_7100669A60(f32 value) {
    bool lowered = false;
    if (value >= 0.0f) {
        if (!(_10a8[_28 ^ 1] & 4)) {
            mCS.lock();
            const u32 idx = _2c;
            if (_10b8[idx] > value) {
                _10b8[idx] = value;
                lowered = true;
            }
            mCS.unlock();
        }
    }
    return lowered;
}

}  // namespace uking
