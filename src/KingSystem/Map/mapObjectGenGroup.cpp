#include "KingSystem/Map/mapObjectGenGroup.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actDebug.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/System/SystemTimers.h"

namespace ksys::map {

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

// NON_MATCHING: the original counts the loop down in bytes (`size << 3`, minus 8 per element)
bool GenGroup::sub_7100D51064() {
    for (auto* obj : mObjects) {
        if (obj->getProc() || !PlacementMgr::instance()->objStuff(obj))
            return false;
    }
    return true;
}

// NON_MATCHING: the original counts the loop down in bytes (`size << 3`, minus 8 per element)
bool GenGroup::sub_7100D51134() {
    for (auto* obj : mObjects) {
        auto* actor = obj->tryGetActor(false);
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

// NON_MATCHING: the original counts the loop down in bytes (`size << 3`, minus 8 per element)
bool GenGroup::x(const u16* id) {
    for (auto* obj : mObjects) {
        if (obj->getId() == *id)
            return false;
    }
    return true;
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
