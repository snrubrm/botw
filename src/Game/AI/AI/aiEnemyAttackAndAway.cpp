#include "Game/AI/AI/aiEnemyAttackAndAway.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

EnemyAttackAndAway::EnemyAttackAndAway(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyAttackAndAway::~EnemyAttackAndAway() = default;

void EnemyAttackAndAway::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

// NON_MATCHING: load order in the XZ distance and the operand order of the normalize multiplies
bool EnemyAttackAndAway::isFinished() const {
    if (ActionBase::isFinished())
        return true;

    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return false;
    if (!isCurrentChild("戦闘攻撃") || !getCurrentChild()->isFinished())
        return true;

    const auto& mtx = mActor->getMtx();
    if (sead::Vector2f(mtx(0, 3) - mTargetPos_d->x, mtx(2, 3) - mTargetPos_d->z).length() >
        *mAwayStartDist_s) {
        return true;
    }

    if (!mActor)
        return false;
    sead::Vector3f dir = mActor->getMtx().getTranslation();
    dir -= *mTargetPos_d;
    dir.y = 0;
    dir.normalize();
    if (sub_710072FEC4(mActor, dir, *mCheckCliffDist_s, nullptr, false, nullptr))
        return true;
    return false;
}

bool EnemyAttackAndAway::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyAttackAndAway::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mAwayStartDist_s, "AwayStartDist");
    getStaticParam(&mCheckCliffDist_s, "CheckCliffDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
