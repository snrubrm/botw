#include "Game/AI/AI/aiSimpleShootingEnemyFindPlayer.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

SimpleShootingEnemyFindPlayer::SimpleShootingEnemyFindPlayer(const InitArg& arg)
    : EnemyBaseFindPlayer(arg) {}

SimpleShootingEnemyFindPlayer::~SimpleShootingEnemyFindPlayer() = default;

bool SimpleShootingEnemyFindPlayer::init_(sead::Heap* heap) {
    return EnemyBaseFindPlayer::init_(heap);
}

void SimpleShootingEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBaseFindPlayer::enter_(params);
}

void SimpleShootingEnemyFindPlayer::calc_() {
    EnemyBaseFindPlayer::calc_();
}

void SimpleShootingEnemyFindPlayer::leave_() {
    EnemyBaseFindPlayer::leave_();
}

void SimpleShootingEnemyFindPlayer::loadParams_() {
    EnemyBaseFindPlayer::loadParams_();
    getStaticParam(&mShootBaseDist_s, "ShootBaseDist");
    getStaticParam(&mShootDistRatio_s, "ShootDistRatio");
}

f32 SimpleShootingEnemyFindPlayer::m34() {
    return *mShootBaseDist_s + sub_71007320F0(mActor, *mWeaponIdx_s) * *mShootDistRatio_s;
}

bool SimpleShootingEnemyFindPlayer::m35() {
    auto* actor = mActor;
    if (!actor)
        return false;
    const auto& target = sub_71005D9330(actor);
    const f32 max_dist = m34();
    if (!inlineIsTargetInReach(target, max_dist, *mAttackVMin_s, *mAttackVMax_s, actor->getMtx(),
                               sead::Mathf::pi(), sead::Mathf::maxNumber(), 0.8f)) {
        return false;
    }
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    return enemy && (enemy->_c48._7c == 2 || enemy->_c48._7c == 5);
}

bool SimpleShootingEnemyFindPlayer::m36(bool b) {
    auto* actor = mActor;
    if (!actor)
        return false;
    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);
    if (sub_710072F788(actor, pos, sub_71005D9330(actor), nullptr))
        return true;
    return m35();
}

// NON_MATCHING: the original tests x in {2, 3} as `(x | 1) != 3` (the base class: `(x & ~1) != 2`)
bool SimpleShootingEnemyFindPlayer::m42(s32 x) {
    return x != 2 && x != 3 && x != 5;
}

bool SimpleShootingEnemyFindPlayer::m43() {
    const s32 state = sub_71005D9744(mActor);
    if (!EnemyBaseFindPlayer::m43())
        return false;
    return m42(state);
}

}  // namespace uking::ai
