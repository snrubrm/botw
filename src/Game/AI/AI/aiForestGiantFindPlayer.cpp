#include "Game/AI/AI/aiForestGiantFindPlayer.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

ForestGiantFindPlayer::ForestGiantFindPlayer(const InitArg& arg) : LargeEnemyFindPlayer(arg) {}

ForestGiantFindPlayer::~ForestGiantFindPlayer() = default;

bool ForestGiantFindPlayer::init_(sead::Heap* heap) {
    if (!LargeEnemyFindPlayer::init_(heap))
        return false;
    sub_71005E2C58(mActor);
    return true;
}

void ForestGiantFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    LargeEnemyFindPlayer::enter_(params);
}

void ForestGiantFindPlayer::leave_() {
    LargeEnemyFindPlayer::leave_();
}

void ForestGiantFindPlayer::loadParams_() {
    LargeEnemyFindPlayer::loadParams_();
}

}  // namespace uking::ai
