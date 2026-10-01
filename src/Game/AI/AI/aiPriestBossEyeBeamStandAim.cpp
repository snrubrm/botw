#include "Game/AI/AI/aiPriestBossEyeBeamStandAim.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

PriestBossEyeBeamStandAim::PriestBossEyeBeamStandAim(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestBossEyeBeamStandAim::~PriestBossEyeBeamStandAim() = default;

bool PriestBossEyeBeamStandAim::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossEyeBeamStandAim::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
}

void PriestBossEyeBeamStandAim::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossEyeBeamStandAim::loadParams_() {
    getStaticParam(&mBorderDist_s, "BorderDist");
    getStaticParam(&mBorderHeight_s, "BorderHeight");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mAimTargetPos_d, "AimTargetPos");
}

}  // namespace uking::ai
