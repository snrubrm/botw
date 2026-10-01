#include "Game/AI/AI/aiGuardianBeam.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

GuardianBeam::GuardianBeam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardianBeam::~GuardianBeam() = default;

bool GuardianBeam::init_(sead::Heap* heap) {
    _40 = mActor->getMainBody();
    _48 = mActor->findPhysicsBodyByName("Atk", "AtkBody");
    if (!_40 || !_48)
        return false;
    return true;
}

void GuardianBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GuardianBeam::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianBeam::loadParams_() {
    getStaticParam(&mMaxDistance_s, "MaxDistance");
}

}  // namespace uking::ai
