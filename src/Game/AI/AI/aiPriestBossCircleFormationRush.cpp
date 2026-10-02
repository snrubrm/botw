#include "Game/AI/AI/aiPriestBossCircleFormationRush.h"
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
