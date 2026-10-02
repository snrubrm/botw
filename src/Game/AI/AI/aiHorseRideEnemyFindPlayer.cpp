#include "Game/AI/AI/aiHorseRideEnemyFindPlayer.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
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

void HorseRideEnemyFindPlayer::calc_() {
    EnemyBaseFindPlayer::calc_();
    sub_71005DB3EC(mActor);
    if (getCurrentChild()->isChangeable() && sub_71003804F4())
        setFailed();
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

bool HorseRideEnemyFindPlayer::m39(const sead::Vector3f& pos, bool b) {
    if (auto* ride_info = mActor->getPlayerRideInfo()) {
        auto* proc = ride_info->_18.getProc(nullptr, ride_info->mActor);
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc)) {
            f32 dist;
            if (auto* nav = actor->m45())
                dist = nav->_2a8 * nav->_2ac;
            else
                dist = 0;
            sead::Vector3f out;
            return sub_710072F944(actor, pos, &out, dist, 3.0f);
        }
    }
    return EnemyBaseFindPlayer::m39(pos, false);
}

}  // namespace uking::ai
