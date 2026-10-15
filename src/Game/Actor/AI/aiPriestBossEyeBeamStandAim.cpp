#include "Game/Actor/AI/aiPriestBossEyeBeamStandAim.h"
#include <cmath>
#include "KingSystem/ActorSystem/actAiInlineParam.h"
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

// 0x71005167ec
// NON_MATCHING: the near-child transition is shared across initial and running paths.
void PriestBossEyeBeamStandAim::calc_() {
    auto* actor = mActor;
    auto* child = getCurrentChild();
    const sead::Vector3f target = *mTargetPos_d;
    const sead::Vector3f position = actor->getMtx().getTranslation();
    const f32 dx = position.x - target.x;
    const f32 dz = position.z - target.z;
    const f32 distance = std::sqrt(dx * dx + dz * dz);
    if (child && isCurrentChild("近距離")) {
        child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            if (auto* controller = mActor->getCharacterController()) {
                controller->sub_7100F5F6FC(sead::Vector3f::zero);
                controller->sub_7100F5FB24(sead::Vector3f::zero);
            }
            setFinished();
        }
        return;
    }
    if (child) {
        child->setDynamicParam(*mAimTargetPos_d, "AimTargetPos");
        child->setDynamicParam(*mTargetPos_d, "TargetPos");
    }
    if (distance < *mBorderDist_s && target.y < *mBorderHeight_s) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("近距離", &pack);
    } else if (!child) {
        sub_7100516B30();
    } else {
        child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            setFinished();
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

// 0x7100516b30
void PriestBossEyeBeamStandAim::sub_7100516B30() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mAimTargetPos_d, "AimTargetPos", -1);
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("遠距離", &pack);
}

}  // namespace uking::ai
