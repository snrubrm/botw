#include "Game/AI/AI/aiKorokPotRootAI.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

KorokPotRootAI::KorokPotRootAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KorokPotRootAI::~KorokPotRootAI() = default;

bool KorokPotRootAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void KorokPotRootAI::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getHomeMtx(&_58);
    _88 = true;
    _89 = false;
    _8c = 0;
    if (*mIsCrayShot_m) {
        mActor->getMainBody()->setMaxImpulse(100.0f);
        mActor->getMainBody()->setGravityFactor(0.3f);
    }
}

void KorokPotRootAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KorokPotRootAI::loadParams_() {
    getStaticParam(&mCrayLaunchSpeedRate_s, "CrayLaunchSpeedRate");
    getStaticParam(&mCrayLaunchAngularSpeed_s, "CrayLaunchAngularSpeed");
    getMapUnitParam(&mCrayLaunchSpeed_m, "CrayLaunchSpeed");
    getMapUnitParam(&mIsCrayShot_m, "IsCrayShot");
}

}  // namespace uking::ai
