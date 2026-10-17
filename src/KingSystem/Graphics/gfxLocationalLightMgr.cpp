#include "KingSystem/Graphics/gfxLocationalLightMgr.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Map/mapObject.h"

namespace ksys::gfx {

bool LocationalLightMgr::sub_7100F13368(ObjectLight* light) {
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
