#include "Game/AI/AI/aiForestGiantFindPlayer.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"

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

void ForestGiantFindPlayer::calc_() {
    LargeEnemyFindPlayer::calc_();
    ksys::act::ActorConstDataAccess accessor;
    auto& link = mActor->getWeapons()->mWeapons[0].link;
    if (link.hasProc()) {
        ksys::act::acquireActor(&link, &accessor);
        if (accessor.hasProc() && accessor.sub_7100D10FB8())
            playerOrEnemyDropWeapon(mActor, &sead::Vector3f::zero, 0, false, false, nullptr, false);
    }
}

void ForestGiantFindPlayer::leave_() {
    LargeEnemyFindPlayer::leave_();
}

void ForestGiantFindPlayer::loadParams_() {
    LargeEnemyFindPlayer::loadParams_();
}

}  // namespace uking::ai
