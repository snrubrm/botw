#include "Game/AI/AI/aiPriestBossEyeBeamFourth.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

PriestBossEyeBeamFourth::PriestBossEyeBeamFourth(const InitArg& arg) : PriestBossEyeBeam(arg) {}

PriestBossEyeBeamFourth::~PriestBossEyeBeamFourth() = default;

bool PriestBossEyeBeamFourth::init_(sead::Heap* heap) {
    return PriestBossEyeBeam::init_(heap);
}

void PriestBossEyeBeamFourth::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossEyeBeam::enter_(params);
    _120 = false;
    _121 = false;
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
}

void PriestBossEyeBeamFourth::leave_() {
    PriestBossEyeBeam::leave_();
}

void PriestBossEyeBeamFourth::loadParams_() {
    PriestBossEyeBeam::loadParams_();
    getStaticParam(&mAtDirType_s, "AtDirType");
    getStaticParam(&mAtAttr_s, "AtAttr");
    getStaticParam(&mAtType_s, "AtType");
    getStaticParam(&mAtShieldBreakPower_s, "AtShieldBreakPower");
    getStaticParam(&mAtImpact_s, "AtImpact");
    getStaticParam(&mAtPowerReduce_s, "AtPowerReduce");
    getStaticParam(&mAtPower_s, "AtPower");
    getStaticParam(&mAtDamage_s, "AtDamage");
    getStaticParam(&mSearchEndAngle_s, "SearchEndAngle");
    getAITreeVariable(&mIsArrivedAtDestination_a, "IsArrivedAtDestination");
    getAITreeVariable(&mDestinationPos_a, "DestinationPos");
    getAITreeVariable(&mFacePos_a, "FacePos");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
