#include "KingSystem/Map/mapObjectGenGroup.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actDebug.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Map/mapPlacementActors.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/System/SystemTimers.h"

namespace ksys::map {

// NON_MATCHING: the original addresses the PtrArray through `this` (no copy of `&mObjects` kept in a second
// callee-saved register) and null-tests `this` before the final size check
void GenGroup::sub_7100D50778(Object* obj) {
    const s32 idx = mObjects.indexOf(obj);
    if (idx < 0)
        return;
    mObjects.erase(idx);
    if (mObjects.size() == 0) {
        mObjects.freeBuffer();
        delete this;
    }
}

bool GenGroup::sub_7100D50E00() {
    if (_0)
        return true;
    if (!_1c)
        return false;
    auto* debug = act::ActorDebug::instance();
    if (!debug)
        return false;
    return debug->hasFlag(act::ActorDebug::Flag::_10000000);
}

bool GenGroup::sub_7100D50E44(bool a1) {
    if (a1) {
        _10.increment();
        return true;
    }
    if (mInitState == 3)
        return false;
    _14.increment();
    return true;
}

void GenGroup::sub_7100D50E90(bool a1) {
    if (a1) {
        _10.decrement();
        mInitState = 0;
        return;
    }
    _14.decrement();
    if (mHasCreateOrDeleteLinks)
        mInitState = 3;
    else if (mInitState == 2)
        mInitState = _18 != 0;
}

bool GenGroup::sub_7100D50EF4(bool a1) {
    auto* timers = SystemTimers::instance();
    if (!timers)
        return false;
    if (mInitState == 3) {
        if (a1 || !_1f || _14 != 0)
            return false;
        _1f = 0;
        mInitState = _18 != 0;
        return false;
    }

    const u32 frame = timers->mFrameCounter;
    if (a1 ? frame == _24 : frame == _20)
        return false;
    if (mInitState == 2)
        return true;
    if (mInitState == 1) {
        if (a1)
            return true;
        if (!mNumExecLinkTag || _10 + _14 != mObjects.size())
            return false;
    } else if (a1) {
        if (_10 != _18)
            return false;
        _24 = frame;
        mInitState = 1;
        return false;
    } else {
        if (_18 || _14 != mObjects.size())
            return false;
    }
    _20 = frame;
    mInitState = 2;
    return false;
}

bool GenGroup::checkContainsObjWithName(const sead::SafeString& name, const u32* mode) {
    for (auto& object : mObjects) {
        const sead::SafeString object_name(object.getUnitConfigName());
        switch (*mode) {
        case 0:
            if (object_name == name)
                return true;
            break;
        case 1:
            if (object_name.include(name))
                return true;
            break;
        case 2:
            if (object_name.startsWith(name))
                return true;
            break;
        case 3:
            if (object_name.endsWith(name))
                return true;
            break;
        }
    }
    return false;
}

bool GenGroup::sub_7100D51064() {
    auto* mgr = PlacementMgr::instance();
    for (auto& obj : mObjects) {
        if (obj.getProc() || !mgr->objStuff(&obj))
            return false;
    }
    return true;
}

bool GenGroup::sub_7100D51134() {
    for (auto& obj : mObjects) {
        auto* actor = obj.tryGetActor(false);
        if (!actor)
            continue;
        if (actor->get1a0())
            return true;
        if (auto* map_obj = actor->getMapObject()) {
            if (map_obj->getFlags0().isOn(Object::Flag0::_20000))
                return true;
        }
    }
    return false;
}

bool GenGroup::x(const u16* id) {
    for (auto& obj : mObjects) {
        if (obj.getId() == *id)
            return false;
    }
    return true;
}

// NON_MATCHING: the original loads the 16-bit flags of the object (ldrh) instead of the low byte (ldrb)
void GenGroup::sub_7100D5119C(Object* obj) {
    if (mInitState == 2)
        return;
    if (_4 == mObjects.size())
        return;

    auto* actors = PlacementMgr::instance()->mPlacementActors;
    if (!_c.compareExchange(0, 1))
        return;

    bool spawned = false;
    for (auto& object : mObjects) {
        if (!spawned && object.getFlags().isOn(Object::Flag::IsLinkTag))
            break;
        spawned |= actors->spawnGenGroupActor(&object, obj);
    }
    _c = 0;
}

void GenGroup::sub_7100D51250(bool a1, u32 a2) {
    for (auto& obj : mObjects) {
        if (a1)
            obj.setFlags0(Object::Flag0(1u << a2));
        else
            obj.resetFlags0(Object::Flag0(1u << a2));
    }
}

void GenGroup::sub_7100D51D78(Object* except) {
    auto* mgr = PlacementMgr::instance();
    if (!mgr)
        return;
    auto* actors = mgr->mPlacementActors;
    if (!actors)
        return;

    for (auto& obj : mObjects) {
        if (&obj == except)
            continue;
        if (!actors->mActorData[obj.getActorDataIdx()].mFlags.isOnBit(ActorData::Flag::OnLowTree))
            continue;

        if (obj.getId() == mgr->_1e4) {
            if (auto* link_data = obj.getLinkData())
                link_data->field_57 = true;
        } else {
            mgr->sub_71011E9C28(&obj, false);
            mgr->disableObjStaticCompound(&obj);
            obj.mFlags0.set(Object::Flag0(0x100400));
        }
    }
}

// NON_MATCHING: same loop; the original computes the end pointer and the odd-count test before it branches on `on`.
void GenGroup::sub_7100D513F4(const u32* bit, bool on) {
    for (auto& obj : mObjects) {
        if (on)
            obj.mHardModeFlags.set(Object::HardModeFlag(1 << *bit));
        else
            obj.mHardModeFlags.reset(Object::HardModeFlag(1 << *bit));
    }
}

// NON_MATCHING: same code, different register allocation (x10 / x11 swapped)
bool GenGroup::sub_7100D51330(const u32* a1) {
    for (auto& obj : mObjects) {
        if (obj.getActorData().mFlags.isOnBit(ActorData::Flag(*a1)))
            return true;
    }
    return false;
}

bool GenGroup::sub_7100D51E6C() {
    s32 count = 0;
    for (auto it = mObjects.begin(), end = mObjects.end(); it != end; ++it) {
        auto* actor = (*it).tryGetActor(false);
        if (actor ? actor->isDeletedOrDeleting() : !(*it).getFlags().isOn(Object::Flag::IsLinkTag))
            ++count;
    }
    return count == mObjects.size() - _18;
}

void GenGroup::sub_7100D510D0() {
    if (_1d)
        return;
    if (auto* timers = SystemTimers::instance()) {
        _1d = 1;
        _28 = timers->mFrameCounter;
    }
}

// NON_MATCHING: the original shares the false return of all three exits and keeps the true one last
u8 GenGroup::sub_7100D510FC() {
    if (!_1d)
        return false;
    auto* timers = SystemTimers::instance();
    if (!timers)
        return false;
    if (timers->mFrameCounter != _28)
        return true;
    return false;
}

}  // namespace ksys::map
