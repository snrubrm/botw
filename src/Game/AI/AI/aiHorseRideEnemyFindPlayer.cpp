#include "Game/AI/AI/aiHorseRideEnemyFindPlayer.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

HorseRideEnemyFindPlayer::HorseRideEnemyFindPlayer(const InitArg& arg) : EnemyBaseFindPlayer(arg) {}

HorseRideEnemyFindPlayer::~HorseRideEnemyFindPlayer() = default;

bool HorseRideEnemyFindPlayer::init_(sead::Heap* heap) {
    return EnemyBaseFindPlayer::init_(heap);
}

void HorseRideEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBaseFindPlayer::enter_(params);
}

void HorseRideEnemyFindPlayer::leave_() {
    EnemyBaseFindPlayer::leave_();
}

void HorseRideEnemyFindPlayer::loadParams_() {
    EnemyBaseFindPlayer::loadParams_();
}

bool HorseRideEnemyFindPlayer::m38() {
    if (auto* ride_info = mActor->getPlayerRideInfo()) {
        auto* proc = ride_info->_18.getProc(nullptr, ride_info->mActor);
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc)) {
            if (auto* nav = actor->m45())
                return (nav->_2a4 & 0xffff) == 0x17;
        }
    }
    return EnemyBaseFindPlayer::m38();
}

}  // namespace uking::ai
