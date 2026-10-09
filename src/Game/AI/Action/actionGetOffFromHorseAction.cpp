#include "Game/AI/Action/actionGetOffFromHorseAction.h"
#include "Game/Actor/actHorseObject.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::action {

GetOffFromHorseAction::GetOffFromHorseAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GetOffFromHorseAction::~GetOffFromHorseAction() = default;

bool GetOffFromHorseAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: null-pointer tracking branches and register scheduling differ.
bool GetOffFromHorseAction::oneShot_() {
    auto* info = mActor->getPlayerRideInfo();
    if (!info)
        return false;
    if (!(info->_30 & 1))
        return true;

    ksys::act::Actor* ridden = nullptr;
    act::Rideable* options = nullptr;
    if (!info->_18.isAccessingSpecifiedProcUnsafe(info->mActor)) {
        ridden = sead::DynamicCast<ksys::act::Actor>(info->_18.getProc(nullptr, info->mActor));
        if (ridden)
            options = ridden->getHorseOptionsMaybe();
    }
    if (options) {
        if (auto* reins = options->m39())
            reins->_850.acquire(nullptr, false);
        if (auto* reins = options->m40()) {
            reins->_850.acquire(nullptr, false);
            reins->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        }
        if (auto* reins = options->m41())
            reins->_850.acquire(nullptr, false);
    }
    if (*mClearDemoMemberIfNotOwned_d) {
        // The original evaluates and discards this event-state query, including the atomic flags read.
        if (!mActor->get1a0()) {
            if (auto* object = mActor->getMapObject())
                object->getFlags0().isOn(ksys::map::Object::Flag0::_20000);
        }
        if (options && !options->sub_7100E8BFF4())
            ridden->m118(true);
    }
    info->sub_7100E7C0EC();
    return true;
}

void GetOffFromHorseAction::loadParams_() {
    getDynamicParam(&mClearDemoMemberIfNotOwned_d, "ClearDemoMemberIfNotOwned");
}

}  // namespace uking::action
