#include "KingSystem/ActorSystem/Profiles/actRopeBase.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Map/mapTypes.h"

namespace ksys::act {

RopeBase::~RopeBase() = default;

bool RopeBase::shouldUnload() {
    if (!_95a && !mMapObject)
        return false;
    return shouldUnloadBecauseOfDistance();
}

int RopeBase::getExtraHeapSize() {
    map::SRT srt{sead::Vector3f::ones, sead::Vector3f::zero, sead::Vector3f::zero};
    mMapObjIter.getSRT(&srt);
    return sead::Mathf::ceil(srt.scale.y * 16384.0f);
}

}  // namespace ksys::act
