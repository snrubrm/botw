#include "Game/AI/AI/aiBeamExplodeBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

BeamExplodeBase::BeamExplodeBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BeamExplodeBase::~BeamExplodeBase() = default;

bool BeamExplodeBase::init_(sead::Heap* heap) {
    _48 = mActor->getMainBody();
    _50 = mActor->findPhysicsBodyByName("Atk", "AtkBody");
    return true;
}

void BeamExplodeBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BeamExplodeBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BeamExplodeBase::loadParams_() {
    getStaticParam(&mMaxDistance_s, "MaxDistance");
    getStaticParam(&mIsDelete_s, "IsDelete");
}

}  // namespace uking::ai
