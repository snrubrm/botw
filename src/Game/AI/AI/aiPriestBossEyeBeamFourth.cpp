#include "Game/AI/AI/aiPriestBossEyeBeamFourth.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
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

void PriestBossEyeBeamFourth::m34() {
    m47(getPlayerPosition());
}

sead::SafeString PriestBossEyeBeamFourth::m46() {
    return "FourthBeam";
}

void PriestBossEyeBeamFourth::m47(const sead::Vector3f& pos) {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "AimTargetPos", -1);
    params.addVec3(getPlayerPosition(), "TargetPos", -1);
    changeChild("索敵", &params);
}

void PriestBossEyeBeamFourth::m48(const sead::Vector3f& pos) {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    changeChild("速攻照準", &params);
}

// NON_MATCHING: the final compare branches to the `true` block at the end (the original falls through to it).
// 0x710051600c (placeholder name): the StandEyeBeamFoot animation is playing and not at its last frame yet
bool PriestBossEyeBeamFourth::sub_710051600C() {
    auto* list = mActor->getASList();
    if (list && list->x_1(0, 0) == "StandEyeBeamFoot") {
        const f32 frame = list->x_5(0, 0, &ksys::as::ASList::Unk2::sub_71011632F8);
        if (frame < list->x_5(0, 0, &ksys::as::ASList::Unk2::sub_710116323C))
            return true;
    }
    return false;
}

}  // namespace uking::ai
