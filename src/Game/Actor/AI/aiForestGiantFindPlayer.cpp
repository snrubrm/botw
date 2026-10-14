#include "Game/Actor/AI/aiForestGiantFindPlayer.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"

namespace uking::ai {

ForestGiantFindPlayer::ForestGiantFindPlayer(const InitArg& arg) : GiantEnemyFindPlayer(arg) {}

ForestGiantFindPlayer::~ForestGiantFindPlayer() = default;

bool ForestGiantFindPlayer::init_(sead::Heap* heap) {
    if (!GiantEnemyFindPlayer::init_(heap))
        return false;
    sub_71005E2C58(mActor);
    return true;
}

void ForestGiantFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantEnemyFindPlayer::enter_(params);
}

void ForestGiantFindPlayer::calc_() {
    GiantEnemyFindPlayer::calc_();
    ksys::act::ActorLinkConstDataAccess accessor;
    auto& link = mActor->getWeapons()->mWeapons[0].link;
    if (link.hasProc()) {
        ksys::act::acquireActor(&link, &accessor);
        if (accessor.hasProc() && accessor.sub_7100D10FB8())
            playerOrEnemyDropWeapon(mActor, &sead::Vector3f::zero, 0, false, false, nullptr, false);
    }
}

void ForestGiantFindPlayer::leave_() {
    GiantEnemyFindPlayer::leave_();
}

void ForestGiantFindPlayer::loadParams_() {
    GiantEnemyFindPlayer::loadParams_();
}

}  // namespace uking::ai
