#include "KingSystem/Graphics/gfxLocationalLightMgr.h"
#include "KingSystem/Map/mapObject.h"

namespace ksys::gfx {

LocationalLightMgr::ObjectLight::ObjectLight() {
    mLights.initOffset(0x28);
}

void LocationalLightMgr::ObjectLight::attachObject(map::Object* object) {
    mObject = object;
    object->_50 = this;
}

void LocationalLightMgr::ObjectLight::detachObject() {
    if (mObject)
        mObject->_50 = nullptr;
    mObject = nullptr;
}

}  // namespace ksys::gfx
