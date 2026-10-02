#include "Game/AI/AI/aiRodEnemyFindPlayer.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"

namespace uking::ai {

RodEnemyFindPlayer::RodEnemyFindPlayer(const InitArg& arg) : LandHumEnemyFindPlayer(arg) {}

RodEnemyFindPlayer::~RodEnemyFindPlayer() = default;

bool RodEnemyFindPlayer::init_(sead::Heap* heap) {
    return LandHumEnemyFindPlayer::init_(heap);
}

void RodEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    LandHumEnemyFindPlayer::enter_(params);
}

void RodEnemyFindPlayer::leave_() {
    LandHumEnemyFindPlayer::leave_();
}

void RodEnemyFindPlayer::loadParams_() {
    LandHumEnemyFindPlayer::loadParams_();
    getStaticParam(&mMagicPer_s, "MagicPer");
    getStaticParam(&mMagicIntervalIntensity_s, "MagicIntervalIntensity");
    getStaticParam(&mMagicCheckInterval_s, "MagicCheckInterval");
    getStaticParam(&mRodWeaponIdx_s, "RodWeaponIdx");
    getStaticParam(&mMagicAttackDir_s, "MagicAttackDir");
}

bool RodEnemyFindPlayer::m54() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;

    if (!(enemy->_e68.value <= sead::Mathf::epsilon()))
        return false;

    if (sead::GlobalRandom::instance()->getF32() * 100.0f < *mMagicPer_s)
        return false;

    sead::Vector3f dir = enemy->getMtx().getTranslation() - sub_71005D9330(mActor);
    const f32 distance = dir.length();
    dir = -dir;
    if (distance > 0)
        dir *= 1.0f / distance;
    if (distance > sub_71007320F0(enemy, *mRodWeaponIdx_s))
        return false;

    sead::Vector3f front;
    enemy->getMtx().getBase(front, 2);
    if (!(dir.dot(front) >= std::cos(*mMagicAttackDir_s)))
        return false;

    if (!isCurrentChild("戦闘") && !isCurrentChild("威嚇") && !isCurrentChild("ナビメッシュ無し") &&
        !isCurrentChild("気づき")) {
        return false;
    }

    const sead::Vector3f pos = enemy->getMtx().getTranslation();
    return !sub_710072E928(pos, sub_71005D9330(enemy), nullptr, nullptr, nullptr, 0.8f);
}

}  // namespace uking::ai
