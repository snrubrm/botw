#include "Game/AI/Action/actionDoorOpenAndClose.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::action {

DoorOpenAndClose::DoorOpenAndClose(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DoorOpenAndClose::~DoorOpenAndClose() = default;

bool DoorOpenAndClose::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DoorOpenAndClose::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
    playAS(mDynASKey_d.cstr(), false, 0, 0, -1.0f);
}

void DoorOpenAndClose::leave_() {
    ksys::act::ai::Action::leave_();
}

void DoorOpenAndClose::loadParams_() {
    getDynamicParam(&mDynASKey_d, "DynASKey");
    getDynamicParam(&mDynOwner_d, "DynOwner");
}

void DoorOpenAndClose::calc_() {
    if (isFinishedAS(0, 0)) {
        setFinished();
        return;
    }

    if (!mDynOwner_d)
        return;
    auto* owner = sead::DynamicCast<ksys::act::Actor>(mDynOwner_d->getProc(nullptr, nullptr));
    if (!owner)
        return;

    bool x;
    {
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        x = player.x_35();
    }
    if (!x)
        return;

    if (auto* list = mActor->getASList()) {
        if (auto* owner_list = owner->getASList())
            list->sub_710115F158(owner_list, 0, 0, 0, 0);
    }
}

}  // namespace uking::action
