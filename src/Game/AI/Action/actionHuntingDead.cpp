#include "Game/AI/Action/actionHuntingDead.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

HuntingDead::HuntingDead(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HuntingDead::~HuntingDead() = default;

void HuntingDead::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getASList()->startAnimationMaybe(-1.0f, -1.0f, "Dead", 0, 0, true);
    if (auto* controller = mActor->getCharacterController()) {
        sub_71001B4AFC(controller);
        controller->sub_7100F5E7F0(0.0f);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
        controller->_a0.getTranslation(_48);
        if (mActor->getASList()->sub_710115AA68("Dead"))
            return;
    }
    setFailed();
}

// NON_MATCHING: the original tail-calls sub_7100F5F458 from both branches, loads the actor's y before _6f0 and
// the InWaterDepth param after the subtraction.
void HuntingDead::sub_71001B4AFC(ksys::phys::CharacterController* controller) {
    if (!controller)
        return;
    auto* actor = mActor;
    const f32 y = actor->getMtx().m[1][3];
    if (actor->get68f() && actor->get6f0() - y > *mInWaterDepth_s) {
        const ksys::act::MotionType current = controller->sub_7100F5F0E4();
        if (int(current) != int(ksys::act::MotionType::Hover))
            controller->sub_7100F5F458(ksys::act::MotionType::Hover);
    } else {
        const ksys::act::MotionType ground = controller->sub_7100F5F0E4();
        if (int(ground) == int(ksys::act::MotionType::_0))
            return;
        const ksys::act::MotionType current = controller->sub_7100F5F0E4();
        if (int(current) != int(ksys::act::MotionType::_1))
            controller->sub_7100F5F458(ksys::act::MotionType::_1);
    }
}

void HuntingDead::leave_() {
    ksys::act::ai::Action::leave_();
}

void HuntingDead::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mIsUseOffsetY_s, "IsUseOffsetY");
    getStaticParam(&mOffsetBoneName_s, "OffsetBoneName");
    getStaticParam(&mExtraOffset_s, "ExtraOffset");
}

// NON_MATCHING: two vector multiplication instructions are scheduled differently.
void HuntingDead::calc_() {
    if (mActor->getASList()->x_4(0, 0)) {
        setFinished();
        return;
    }
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    sub_71001B4AFC(controller);
    if (!mOffsetBoneName_s.isEmpty()) {
        const auto key = mActor->getModel()->searchBone(mOffsetBoneName_s);
        if (key.isValid()) {
            sead::Matrix34f bone_matrix;
            mActor->getModel()->getUnits()(key.model_unit_index)->mModelUnit->getBoneWorldMatrix(
                &bone_matrix, key.bone_index);
            const auto& actor_matrix = mActor->getMtx();
            sead::Vector3f difference{bone_matrix(0, 3) - actor_matrix(0, 3),
                                     bone_matrix(1, 3) - actor_matrix(1, 3),
                                     bone_matrix(2, 3) - actor_matrix(2, 3)};
            if (!*mIsUseOffsetY_s)
                difference.y = 0.0f;
            const sead::Vector3f local_offset{
                difference.x * actor_matrix(0, 0) + difference.y * actor_matrix(1, 0) +
                    difference.z * actor_matrix(2, 0),
                difference.x * actor_matrix(0, 1) + difference.y * actor_matrix(1, 1) +
                    difference.z * actor_matrix(2, 1),
                difference.x * actor_matrix(0, 2) + difference.y * actor_matrix(1, 2) +
                    difference.z * actor_matrix(2, 2)};
            const auto extra_offset = *mExtraOffset_s * mActor->getScale().x;
            controller->sub_7100F605C8(extra_offset + (_48 - local_offset));
        }
    }
    controller->sub_7100F5E7F0(0.0f);
    controller->sub_7100F5FFE8(&sead::Vector3f::zero, false);
}

}  // namespace uking::action
