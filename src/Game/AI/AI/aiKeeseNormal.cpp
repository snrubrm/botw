#include "Game/AI/AI/aiKeeseNormal.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physRayCastForRequest.h"

namespace uking::ai {

KeeseNormal::KeeseNormal(const InitArg& arg) : EnemyNormal(arg) {}

KeeseNormal::~KeeseNormal() = default;

bool KeeseNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void KeeseNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getHomePos(&_430);
    _43c = _430;
    EnemyNormal::enter_(params);
    _448 = false;
    _44c = ksys::Timer(0, 0, 1);
    setDamageCallbackTiming(mActor, 1, &_460);
}

void KeeseNormal::leave_() {
    if (_458) {
        _458->release();
        _458 = nullptr;
    }
    sub_71005DA114(mActor, &_460);
    EnemyNormal::leave_();
}

void KeeseNormal::loadParams_() {
    EnemyNormal::loadParams_();
    getStaticParam(&mRoamHeightFromGlowObj_s, "RoamHeightFromGlowObj");
    getMapUnitParam(&mIsCreateOnFace_m, "IsCreateOnFace");
}

bool KeeseNormal::handleMessage_(const ksys::Message& message) {
    if (isChangeable() && _3e0.m2(message))
        return !isCurrentChild("ぶらさがり");
    if (isCurrentChild("ぶらさがり"))
        return false;
    return EnemyNormal::handleMessage_(message);
}

}  // namespace uking::ai
