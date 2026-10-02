#include "Game/AI/AI/aiWeaponRootAI.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

WeaponRootAI::WeaponRootAI(const InitArg& arg) : ksys::act::ai::Ai(arg), _c8() {}

WeaponRootAI::~WeaponRootAI() = default;

bool WeaponRootAI::init_(sead::Heap* heap) {
    if (auto* body = mActor->findPhysicsBodyByName(ksys::act::getStr_Body().cstr(), "Body"))
        _b0 = body->getMaxAngularVelocity();
    return true;
}

void WeaponRootAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WeaponRootAI::leave_() {
    _c8.fadeXLink();
}

void WeaponRootAI::loadParams_() {
    getStaticParam(&mBlinkFrame_s, "BlinkFrame");
    getStaticParam(&mFallOutSpeed_s, "FallOutSpeed");
    getStaticParam(&mLandNoiseLevel_s, "LandNoiseLevel");
    getMapUnitParam(&mIsFixedPlace_m, "IsFixedPlace");
    getMapUnitParam(&mIsEmitLandNoise_m, "IsEmitLandNoise");
}

void WeaponRootAI::m36() {}

void WeaponRootAI::m37() {}

void WeaponRootAI::m38() {}

void WeaponRootAI::m39() {}

void WeaponRootAI::m40() {}

void WeaponRootAI::m45() {
    ksys::act::enableAllAttClients(mActor);
    ksys::act::disableAttClient(mActor, "CatchBoomerang");
}

}  // namespace uking::ai
