#include "Game/AI/AI/aiHorseRideShooterFindPlayer.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

HorseRideShooterFindPlayer::HorseRideShooterFindPlayer(const InitArg& arg)
    : SimpleShootingEnemyFindPlayer(arg) {}

HorseRideShooterFindPlayer::~HorseRideShooterFindPlayer() = default;

bool HorseRideShooterFindPlayer::init_(sead::Heap* heap) {
    return SimpleShootingEnemyFindPlayer::init_(heap);
}

void HorseRideShooterFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleShootingEnemyFindPlayer::enter_(params);
}

void HorseRideShooterFindPlayer::calc_() {
    SimpleShootingEnemyFindPlayer::calc_();
}

void HorseRideShooterFindPlayer::leave_() {
    SimpleShootingEnemyFindPlayer::leave_();
}

void HorseRideShooterFindPlayer::loadParams_() {
    SimpleShootingEnemyFindPlayer::loadParams_();
}

bool HorseRideShooterFindPlayer::m38() {
    if (auto* ride_info = mActor->getPlayerRideInfo()) {
        auto* proc = ride_info->_18.getProc(nullptr, ride_info->mActor);
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc)) {
            if (auto* nav = actor->m45())
                return (nav->_2a4 & 0xffff) == 0x17;
        }
    }
    return SimpleShootingEnemyFindPlayer::m38();
}

}  // namespace uking::ai
