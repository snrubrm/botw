#include "Game/Actor/actNoCalcActor.h"
#include <basis/seadNew.h>
#include "KingSystem/Map/mapObject.h"

namespace uking::act {

NoCalcActor::NoCalcActor(const CreateArg& arg) : Actor(arg) {
    getJobHandler(ksys::act::JobType::Calc1) = nullptr;
    getJobHandler(ksys::act::JobType::Calc2) = nullptr;
    _1c0 = 3;
}

ksys::act::BaseProc* NoCalcActor::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) NoCalcActor(arg);
}

bool NoCalcActor::shouldSkipJobPush_(ksys::act::JobType type) {
    if (type == ksys::act::JobType::PreCalc && !_1a0) {
        if (!mMapObject || !mMapObject->getFlags0().isOn(ksys::map::Object::Flag0::_20000))
            return true;
    }
    return Actor::shouldSkipJobPush_(type);
}

void NoCalcActor::onJobPush2_(ksys::act::JobType type) {
    if (type == ksys::act::JobType::PreCalc && !_1a0) {
        if (!mMapObject || !mMapObject->getFlags0().isOn(ksys::map::Object::Flag0::_20000)) {
            deleteIfPlacementStuff();
            decrementSkipJobPushTimer();
            if (shouldSkipJobPush(ksys::act::JobType::PreCalc)) {
                x_14(true);
                x_16();
                handleModelFadeInOutAndFadeDelete();
            }
            return;
        }
    }
    Actor::onJobPush2_(type);
}

}  // namespace uking::act
