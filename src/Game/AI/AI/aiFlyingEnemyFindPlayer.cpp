#include "Game/AI/AI/aiFlyingEnemyFindPlayer.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::ai {

FlyingEnemyFindPlayer::FlyingEnemyFindPlayer(const InitArg& arg) : EnemyBaseFindPlayer(arg) {}

FlyingEnemyFindPlayer::~FlyingEnemyFindPlayer() = default;

bool FlyingEnemyFindPlayer::init_(sead::Heap* heap) {
    return EnemyBaseFindPlayer::init_(heap);
}

void FlyingEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBaseFindPlayer::enter_(params);
}

void FlyingEnemyFindPlayer::calc_() {
    EnemyBaseFindPlayer::calc_();
}

void FlyingEnemyFindPlayer::leave_() {
    EnemyBaseFindPlayer::leave_();
}

void FlyingEnemyFindPlayer::loadParams_() {
    EnemyBaseFindPlayer::loadParams_();
}

// NON_MATCHING: translation copy / evaluation order (as EnemyBaseFindPlayer::m35)
bool FlyingEnemyFindPlayer::m35() {
    auto* actor = mActor;
    if (!actor)
        return false;
    const auto& target = sub_71005D9330(actor);
    const f32 max_dist = *mAttackRange_s + sub_71007320F0(actor, *mWeaponIdx_s);
    if (!sub_710072DEF0(target, max_dist, *mAttackVMin_s, *mAttackVMax_s,
                        actor->getMtx().getTranslation(), actor->getMtx().getBase(2),
                        sead::Mathf::pi(), 0.8f, 1.2f)) {
        return false;
    }
    return sub_71003D2E30(sub_71005D960C(mActor));
}

bool FlyingEnemyFindPlayer::m36(bool b) {
    return sub_71003D2E30(sub_71005D960C(mActor));
}

bool FlyingEnemyFindPlayer::m37() {
    sead::Vector3f pos = sub_71005D98D8(mActor);
    pos.y += 0.8f;
    return sub_71003D2E30(pos);
}

}  // namespace uking::ai
