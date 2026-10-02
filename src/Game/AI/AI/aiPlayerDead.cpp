#include "Game/AI/AI/aiPlayerDead.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

PlayerDead::PlayerDead(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerDead::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerDead::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerDead::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_c48.reset(1);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_10);
    if (auto* controller = mActor->getCharacterController())
        controller->mFlags.set(8);
}

void PlayerDead::loadParams_() {
    getStaticParam(&mRumbleType_s, "RumbleType");
    getStaticParam(&mRumblePower_s, "RumblePower");
}

}  // namespace uking::ai
