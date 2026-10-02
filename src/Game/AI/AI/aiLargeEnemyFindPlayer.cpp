#include "Game/AI/AI/aiLargeEnemyFindPlayer.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::ai {

LargeEnemyFindPlayer::LargeEnemyFindPlayer(const InitArg& arg) : EnemyBaseFindPlayer(arg) {}

LargeEnemyFindPlayer::~LargeEnemyFindPlayer() = default;

bool LargeEnemyFindPlayer::init_(sead::Heap* heap) {
    return EnemyBaseFindPlayer::init_(heap);
}

void LargeEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBaseFindPlayer::enter_(params);
}

void LargeEnemyFindPlayer::calc_() {
    EnemyBaseFindPlayer::calc_();
}

void LargeEnemyFindPlayer::leave_() {
    EnemyBaseFindPlayer::leave_();
}

void LargeEnemyFindPlayer::loadParams_() {
    EnemyBaseFindPlayer::loadParams_();
}

bool LargeEnemyFindPlayer::m35() {
    if (!sub_710072E1B4(mActor, false))
        return false;
    return EnemyBaseFindPlayer::m35();
}

}  // namespace uking::ai
