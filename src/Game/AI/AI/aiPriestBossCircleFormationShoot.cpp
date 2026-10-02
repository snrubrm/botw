#include "Game/AI/AI/aiPriestBossCircleFormationShoot.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

PriestBossCircleFormationShoot::PriestBossCircleFormationShoot(const InitArg& arg)
    : PriestBossFormation(arg) {}

PriestBossCircleFormationShoot::~PriestBossCircleFormationShoot() = default;

bool PriestBossCircleFormationShoot::init_(sead::Heap* heap) {
    return PriestBossFormation::init_(heap);
}

void PriestBossCircleFormationShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossFormation::enter_(params);
    m43();
}

void PriestBossCircleFormationShoot::leave_() {
    PriestBossFormation::leave_();
}

void PriestBossCircleFormationShoot::loadParams_() {
    PriestBossFormation::loadParams_();
    getStaticParam(&mHomingAttackTime_s, "HomingAttackTime");
}

bool PriestBossCircleFormationShoot::m36() {
    if (isCurrentChild("陣形作成後待機"))
        return false;
    return PriestBossFormation::m36();
}

void PriestBossCircleFormationShoot::m43() {
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
