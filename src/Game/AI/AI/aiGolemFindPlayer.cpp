#include "Game/AI/AI/aiGolemFindPlayer.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

GolemFindPlayer::GolemFindPlayer(const InitArg& arg) : LargeEnemyFindPlayer(arg) {}

GolemFindPlayer::~GolemFindPlayer() = default;

bool GolemFindPlayer::init_(sead::Heap* heap) {
    return LargeEnemyFindPlayer::init_(heap);
}

void GolemFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    LargeEnemyFindPlayer::enter_(params);
}

void GolemFindPlayer::leave_() {
    LargeEnemyFindPlayer::leave_();
}

void GolemFindPlayer::loadParams_() {
    LargeEnemyFindPlayer::loadParams_();
    getStaticParam(&mSearchExplosiveDist_s, "SearchExplosiveDist");
}

// NON_MATCHING: the original loads mActor for the first argument after the call
void GolemFindPlayer::m47() {
    sub_71005DB068(mActor, sub_71005D9330(mActor));
}

}  // namespace uking::ai
