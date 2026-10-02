#include "Game/AI/AI/aiGuardianMiniFindPlayer.h"
#include "Game/AI/AI/aiGuardianMiniRoot.h"

namespace uking::ai {

GuardianMiniFindPlayer::GuardianMiniFindPlayer(const InitArg& arg) : LandHumEnemyFindPlayer(arg) {}

GuardianMiniFindPlayer::~GuardianMiniFindPlayer() = default;

void GuardianMiniFindPlayer::loadParams_() {
    LandHumEnemyFindPlayer::loadParams_();
}

bool GuardianMiniFindPlayer::m42(s32 x) {
    if (sub_71004282EC(mActor))
        return false;
    return LandHumEnemyFindPlayer::m42(x);
}

bool GuardianMiniFindPlayer::m43() {
    if (sub_71004282EC(mActor))
        return false;
    return LandHumEnemyFindPlayer::m43();
}

}  // namespace uking::ai
