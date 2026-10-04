#include "Game/AI/AI/aiEnemyPursuingBattle.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyLevel.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyPursuingBattle::EnemyPursuingBattle(const InitArg& arg) : EnemyBattle(arg) {}

EnemyPursuingBattle::~EnemyPursuingBattle() = default;

void EnemyPursuingBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void EnemyPursuingBattle::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("追撃ち攻撃")) {
            sub_7100381ED4();
            m37();
            return;
        }
    }

    if (getCurrentChild()->isChangeable()) {
        if (isCurrentChild("戦闘準備") && sub_71003A9AE8()) {
            changeToFollowUpAttack();
            return;
        }
    }

    EnemyBattle::calc_();
    if (isCurrentChild("戦闘準備") && !(_a8.value <= sead::Mathf::epsilon()))
        _a8.update();
}

// NON_MATCHING: the original keeps the forward vector's x/z in integer registers (copied with integer loads),
// re-reads mActor from `this` for the later calls and loads the target before the actor's position;
// structure and constants match.
bool EnemyPursuingBattle::sub_71003A9AE8() {
    auto* actor = mActor;
    if (!actor)
        return false;
    const auto* level = actor->getParam()->getRes().mGParamList->getEnemyLevel();
    if (!level || !*level->mIsBackSwiftAttack)
        return false;
    if (!(_a8.value <= sead::Mathf::epsilon()))
        return false;
    if (!sub_710072E1B4(actor, false))
        return false;
    if (!sub_710072DDB8(sub_71005D9330(actor), actor->getMtx(), *mAttackAngle_s))
        return false;

    const sead::Matrix34f& mtx = sub_71005D96A8(actor);
    sead::Vector3f forward = mtx.getBase(2);
    forward.y = 0;
    forward.normalize();
    const sead::Vector3f& target_pos = sub_71005D9330(actor);
    sead::Vector3f to_target = target_pos - actor->getMtx().getTranslation();
    to_target.y = 0;
    to_target.normalize();
    if (forward.dot(-to_target) > sead::Mathf::cos(*mPursuingAttackStartAng_s))
        return false;

    const sead::Vector3f target = sub_71005D9330(actor);
    auto* nav = actor->m45();
    return sub_710072F944(actor, target, nullptr, nav ? nav->getRadiusMaybe() : 0.0f, 3.0f);
}

void EnemyPursuingBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mPursuingAttackInterval_s, "PursuingAttackInterval");
    getStaticParam(&mPursuingAttackIntervalRand_s, "PursuingAttackIntervalRand");
    getStaticParam(&mPursuingAttackStartAng_s, "PursuingAttackStartAng");
}

void EnemyPursuingBattle::changeToFollowUpAttack() {
    const s32 rand = *mPursuingAttackIntervalRand_s;
    const f32 random_part = rand * -0.5f;
    const f32 interval = *mPursuingAttackInterval_s;
    _a8.reset(s32(interval + random_part) + s32(sead::GlobalRandom::instance()->getU32(rand)));

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("追撃ち攻撃", &pack);
}

}  // namespace uking::ai
