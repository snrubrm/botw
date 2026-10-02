#include "Game/AI/AI/aiFlyingEnemyFindPlayer.h"
#include "Game/AI/aiUnk_71005D6D10.h"

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

bool FlyingEnemyFindPlayer::m36(bool b) {
    return sub_71003D2E30(sub_71005D960C(mActor));
}

bool FlyingEnemyFindPlayer::m37() {
    sead::Vector3f pos = sub_71005D98D8(mActor);
    pos.y += 0.8f;
    return sub_71003D2E30(pos);
}

}  // namespace uking::ai
