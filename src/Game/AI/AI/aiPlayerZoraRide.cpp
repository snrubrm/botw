#include "Game/AI/AI/aiPlayerZoraRide.h"
#include "Game/AI/aiUnk_710087CE34.h"
#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

PlayerZoraRide::PlayerZoraRide(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PlayerZoraRide::~PlayerZoraRide() = default;

bool PlayerZoraRide::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerZoraRide::enter_(ksys::act::ai::InlineParamPack* params) {
    static_cast<ksys::act::Player*>(mActor)->sub_7100881104();
    _d8 = false;
    _d9 = true;
    if (!mActor->getConnectedCalcParent()) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::Attention::instance()->sub_7100D7482C(&accessor))
            accessor.setThisActorAsParent(mActor, false);
    }
    sub_71008732C8(mActor);
    if (!handlePendingChildChange())
        changeChild("乗り");
}

void PlayerZoraRide::leave_() {
    if (_d8)
        mActor->sub_71011DA834(&_38);
    mActor->resetConnectedCalcParent(false);
    sub_7100873264(mActor);
}

void PlayerZoraRide::loadParams_() {}

}  // namespace uking::ai
