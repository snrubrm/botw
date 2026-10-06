#include "Game/AI/Action/actionWarpMyHorse.h"
#include "Game/gameHorseMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

WarpMyHorse::WarpMyHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpMyHorse::~WarpMyHorse() = default;

bool WarpMyHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpMyHorse::loadParams_() {
    getDynamicParam(&mPositionX_d, "PositionX");
    getDynamicParam(&mPositionY_d, "PositionY");
    getDynamicParam(&mPositionZ_d, "PositionZ");
    getDynamicParam(&mDirection_d, "Direction");
}

bool WarpMyHorse::oneShot_() {
    auto& link = HorseMgr::instance()->mOwnedHorse;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&link, &accessor);
    const sead::Vector3f rotation(0, sead::Mathf::deg2rad(*mDirection_d), 0);
    const sead::Vector3f translation(*mPositionX_d, *mPositionY_d, *mPositionZ_d);
    _40.makeSRT(sead::Vector3f::ones, rotation, translation);
    mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3800015), &_40, true);
    return true;
}

}  // namespace uking::action
