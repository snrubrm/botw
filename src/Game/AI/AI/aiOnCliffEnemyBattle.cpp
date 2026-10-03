#include "Game/AI/AI/aiOnCliffEnemyBattle.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

OnCliffEnemyBattle::OnCliffEnemyBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

OnCliffEnemyBattle::~OnCliffEnemyBattle() = default;

bool OnCliffEnemyBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void OnCliffEnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    const int counter = *mLostCounter_s;
    const int counter2 = counter * 1.1f;
    _6c = sead::Mathi::min(counter, counter2);
    _70 = sead::Mathi::max(counter, counter2);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D960C(mActor), "TargetPos", -1);
    changeChild("追跡", &pack);
}

bool OnCliffEnemyBattle::m34() {
    auto* actor = mActor;
    const sead::Vector3f pos = actor->getMtx().getTranslation();
    sead::Vector3f dir = pos - sub_71005D960C(actor);
    dir.negate();
    const f32 dist = dir.normalize();
    if (dist > *mAttackDist_s)
        return false;

    sead::Matrix34f inv;
    sead::Matrix34CalcCommon<f32>::inverse(inv, actor->getMtx());
    sead::Vector3f local;
    local.setRotated(inv, dir);

    const f32 angle_h = sead::Mathf::abs(ksys::util::sub_71011EF0CC(std::atan2(local.x, local.z)));
    if (angle_h > *mAttackAngleH_s)
        return false;

    const f32 angle_v = ksys::util::sub_71011EF0CC(
        std::atan2(local.y, std::sqrt(local.x * local.x + local.z * local.z)));
    return *mAttackAngleVMin_s < angle_v && angle_v < *mAttackAngleVMax_s;
}

void OnCliffEnemyBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void OnCliffEnemyBattle::loadParams_() {
    getStaticParam(&mLostCounter_s, "LostCounter");
    getStaticParam(&mAttackDist_s, "AttackDist");
    getStaticParam(&mAttackAngleH_s, "AttackAngleH");
    getStaticParam(&mAttackAngleVMax_s, "AttackAngleVMax");
    getStaticParam(&mAttackAngleVMin_s, "AttackAngleVMin");
    getStaticParam(&mAttackIntervalIntensity_s, "AttackIntervalIntensity");
}

}  // namespace uking::ai
