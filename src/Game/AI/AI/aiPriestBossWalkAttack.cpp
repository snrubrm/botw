#include "Game/AI/AI/aiPriestBossWalkAttack.h"
#include <cmath>
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

PriestBossWalkAttack::PriestBossWalkAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestBossWalkAttack::~PriestBossWalkAttack() = default;

bool PriestBossWalkAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original's NaN / zero tests of `dir` go z, y, x (ours x, y, z), which swaps the registers of
// dir.x / dir.z; the acos clamp is laid out min-first with a different register choice
void PriestBossWalkAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* nav = mActor->m45();
    if (!nav) {
        setFailed();
        return;
    }

    nav->inlineReset();
    nav->sub_7100F75F8C(*mTargetPos_d);
    nav->sub_7100F7604C(*mGoalDistanceTolerance_s);

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f dir = *mTargetPos_d - pos;
    dir.y = 0.0f;
    dir.normalize();
    if (dir.isNan() || dir == sead::Vector3f(0, 0, 0))
        dir = front;

    const f32 angle = sead::Mathf::acos(sead::Mathf::clamp(front.dot(dir), -1.0f, 1.0f));
    if (angle > *mAngleNeedTurn_s) {
        ksys::act::ai::InlineParamPack child_params;
        child_params.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("回転", &child_params);
    } else {
        ksys::act::ai::InlineParamPack child_params;
        child_params.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("待機", &child_params);
    }
    _98 = false;
}

void PriestBossWalkAttack::leave_() {
    sub_71007A2E04(mActor);
}

void PriestBossWalkAttack::loadParams_() {
    getStaticParam(&mAtDirType_s, "AtDirType");
    getStaticParam(&mAtAttr_s, "AtAttr");
    getStaticParam(&mAtType_s, "AtType");
    getStaticParam(&mAtShieldBreakPower_s, "AtShieldBreakPower");
    getStaticParam(&mAtImpact_s, "AtImpact");
    getStaticParam(&mAtPowerReduce_s, "AtPowerReduce");
    getStaticParam(&mAtPower_s, "AtPower");
    getStaticParam(&mAtDamage_s, "AtDamage");
    getStaticParam(&mGoalDistanceTolerance_s, "GoalDistanceTolerance");
    getStaticParam(&mAngleNeedTurn_s, "AngleNeedTurn");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

// 0x7100531900
void PriestBossWalkAttack::sub_7100531900() {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const sead::Vector3f& player_pos = getPlayerPosition();
    const f32 dx = pos.x - player_pos.x;
    const f32 dz = pos.z - player_pos.z;
    const f32 distance = std::sqrt(dx * dx + dz * dz);
    mActor->getASList()->x_6(0x10, 0, distance);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("移動", &pack);
}

}  // namespace uking::ai
