#include "Game/AI/AI/aiPlayerZoraRide.h"
#include "Game/AI/aiUnk_710087CE34.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

PlayerZoraRide::PlayerZoraRide(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PlayerZoraRide::~PlayerZoraRide() = default;

bool PlayerZoraRide::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerZoraRide::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerZoraRide::leave_() {
    if (_d8)
        mActor->sub_71011DA834(&_38);
    mActor->resetConnectedCalcParent(false);
    sub_7100873264(mActor);
}

void PlayerZoraRide::loadParams_() {}

}  // namespace uking::ai
