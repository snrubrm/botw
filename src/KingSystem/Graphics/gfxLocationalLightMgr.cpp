#include "KingSystem/Graphics/gfxLocationalLightMgr.h"
#include "KingSystem/Graphics/gfxLocationalLightRig.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Map/mapObject.h"

namespace ksys::gfx {

// Shared light threshold read through the manager getter 0x7100f143fc.
static f32 sUnk_71024F3CC8 = 0.007f;
// 0x71024f3cc4 (.data, 0.3f): the lower light threshold. External linkage keeps the load: the
// original reads it as mutable data, it is not folded to the initial value.
KSYS_VISIBILITY_HIDDEN f32 sUnk_71024F3CC4 = 0.3f;

f32 LocationalLightMgr::sub_7100F143E4() const {
    return sUnk_71024F3CC4 < 0.001f ? 0.001f : sUnk_71024F3CC4;
}

f32 LocationalLightMgr::sub_7100F143FC() const {
    return sUnk_71024F3CC8;
}

void LocationalLightMgr::RigLightPool::init(s32 capacity, sead::Heap* heap) {
    mLights.tryAllocBuffer(capacity, heap, 8);
    mFreeLights.allocBuffer(capacity, heap, 8);
    mActiveLights.allocBuffer(capacity, heap, 8);
    // Native iterates the requested count, including the Buffer bounds fallback
    // if the nothrow record allocation failed. Do not turn this into range-for.
    for (s32 i = 0; i < capacity; ++i)
        mFreeLights.pushBack(&mLights[i]);
}

LocationalLightMgr::ObjectLight::Light* LocationalLightMgr::RigLightPool::allocate() {
    auto lock = sead::makeScopedLock(mCS);
    auto* light = mFreeLights.popBack();
    if (light)
        mActiveLights.pushBack(light);
    return light;
}

// NON_MATCHING: the original walks the active array with a pointer loop; ours compares the
// pointer range and index separately. Same result.
bool LocationalLightMgr::RigLightPool::release(ObjectLight::Light* light) {
    auto lock = sead::makeScopedLock(mCS);
    s32 index = 0;
    for (auto* it = mActiveLights.dataBegin(); it != mActiveLights.dataEnd(); ++it, ++index) {
        if (*it == light) {
            mActiveLights.erase(index);
            mFreeLights.pushBack(light);
            return true;
        }
    }
    return false;
}

// NON_MATCHING: the original sets the bit with `(_60 & 0x20000000) + 0x20000000 | _60`, which also
// carries into bit 30 when bit 29 was already set.
void LocationalLightMgr::sub_7100F1334C() {
    _60 |= 0x20000000;
}

bool LocationalLightMgr::RenderLightPool::release(Unk_7102519378* light) {
    auto lock = sead::makeScopedLock(mCS);
    s32 index = 0;
    for (auto* it = mActiveLights.dataBegin(); it != mActiveLights.dataEnd(); ++it, ++index) {
        if (*it == light) {
            mActiveLights.erase(index);
            mFreeLights.pushBack(light);
            return true;
        }
    }
    return false;
}

bool LocationalLightMgr::sub_7100F13368(ObjectLight* light) {
    static_assert(offsetof(LocationalLightMgr, mRigLightPool) == 0x458);
    static_assert(offsetof(LocationalLightMgr, mObjectLightCS) == 0x4c8);
    if (light)
        light->detachObject();
    auto lock = sead::makeScopedLock(mObjectLightCS);
    s32 index = 0;
    for (auto& active : mActiveObjectLights) {
        if (&active == light) {
            mActiveObjectLights.erase(index);
            mFreeObjectLights.pushBack(light);
            return true;
        }
        ++index;
    }
    return false;
}

void LocationalLightMgr::sub_7100F13420(gsys::ModelUnit* unit) {
    auto lock = sead::makeScopedLock(mCS);
    if (!unit)
        return;
    auto light_lock = sead::makeScopedLock(mObjectLightCS);
    auto* placement_mgr = map::PlacementMgr::instance();
    auto end = mActiveObjectLights.end();
    for (auto it = mActiveObjectLights.begin(); it != end;) {
        auto* object = it->mObject;
        if (placement_mgr->mPlacementActors->mActorData[object->getActorDataIdx()]._10 == unit) {
            sub_7100F0EC30(object);
            it = mActiveObjectLights.begin();
            end = mActiveObjectLights.end();
        } else {
            ++it;
        }
    }
}

void LocationalLightMgr::sub_7100F134E8(map::Object* first, map::Object* last) {
    auto lock = sead::makeScopedLock(mCS);
    auto end = mActiveObjectLights.end();
    for (auto it = mActiveObjectLights.begin(); it != end;) {
        auto* object = it->mObject;
        if (object > first && object < last) {
            sub_7100F0EC30(object);
            it = mActiveObjectLights.begin();
            end = mActiveObjectLights.end();
        } else {
            ++it;
        }
    }
}

}  // namespace ksys::gfx
