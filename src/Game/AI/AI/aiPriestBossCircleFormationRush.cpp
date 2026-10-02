#include "Game/AI/AI/aiPriestBossCircleFormationRush.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

PriestBossCircleFormationRush::PriestBossCircleFormationRush(const InitArg& arg)
    : PriestBossFormation(arg) {}

PriestBossCircleFormationRush::~PriestBossCircleFormationRush() = default;

bool PriestBossCircleFormationRush::init_(sead::Heap* heap) {
    return PriestBossFormation::init_(heap);
}

void PriestBossCircleFormationRush::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossFormation::enter_(params);
    if (auto* controller = mActor->getCharacterController())
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityNPC);
    m43();
}

void PriestBossCircleFormationRush::calc_() {
    PriestBossFormation::calc_();
    if (auto* controller = mActor->getCharacterController())
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityNPC);

    auto* child = getCurrentChild();
    if (!child)
        return;

    if (isCurrentChild("攻撃")) {
        if (*mHomingAttackTime_s >= 0) {
            if (_88.value <= sead::Mathf::epsilon())
                return;
            _88.update();
        }
        child->setDynamicParam(sub_71005D93CC(mActor), "TargetPos");
        return;
    }

    if (!isCurrentChild("陣形作成後待機"))
        return;

    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    sead::Vector3f pos = sead::Vector3f::zero;
    if (!unit || !unit->sub_710071A020(&pos, unit->sub_7100719534(mActor)))
        return;

    child->setDynamicParam(pos, "TargetPos");
    if (child->isFinished() || child->isFailed()) {
        if (auto* body = mActor->getPhysicsMainBody()) {
            body->setLinearVelocity(sead::Vector3f::zero);
            body->setAngularVelocity(sead::Vector3f::zero);
        }
        ksys::act::ai::InlineParamPack params;
        params.addVec3(pos, "TargetPos", -1);
        changeChild("陣形作成後待機", &params);
    }
}

void PriestBossCircleFormationRush::leave_() {
    PriestBossFormation::leave_();
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F60604();
}

void PriestBossCircleFormationRush::loadParams_() {
    PriestBossFormation::loadParams_();
    getStaticParam(&mHomingAttackTime_s, "HomingAttackTime");
}

bool PriestBossCircleFormationRush::m36() {
    if (isCurrentChild("陣形作成後待機"))
        return false;
    return PriestBossFormation::m36();
}

void PriestBossCircleFormationRush::m43() {
    if (isCurrentChild("陣形作成_現れる")) {
        auto* unit = sead::DynamicCast<Unk_7102450fa8>(
            *static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
        if (unit) {
            ksys::act::ai::InlineParamPack params;
            sead::Vector3f pos = sead::Vector3f::zero;
            unit->sub_710071A020(&pos, unit->sub_7100719534(mActor));
            params.addVec3(pos, "TargetPos", -1);
            changeChild("陣形作成後待機", &params);
            return;
        }
    }
    changeChild("待機");
}

}  // namespace uking::ai
