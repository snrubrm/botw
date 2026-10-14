#include "Game/Actor/Action/actionNpcRideWaitAction.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

NpcRideWaitAction::NpcRideWaitAction(const InitArg& arg) : NPCWaitAction(arg) {}

NpcRideWaitAction::~NpcRideWaitAction() = default;

bool NpcRideWaitAction::init_(sead::Heap* heap) {
    return NPCWaitAction::init_(heap);
}

void NpcRideWaitAction::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getASList()->x_6(10, 0, *mGearSpeed_d);
    _40 = *mGearSpeed_d;
    NPCWaitAction::enter_(params);
}

void NpcRideWaitAction::leave_() {
    NPCWaitAction::leave_();
}

void NpcRideWaitAction::loadParams_() {
    NPCWaitAction::loadParams_();
    getDynamicParam(&mGearSpeed_d, "GearSpeed");
}

void NpcRideWaitAction::calc_() {
    NPCWaitAction::calc_();
    if (!mActor || !mActor->getPlayerRideInfo()) {
        setFailed();
        return;
    }

    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5EDD8(1.0f);

    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&mActor->getPlayerRideInfo()->_18, &accessor);
    _40 = static_cast<f32>(int(accessor.sub_7100D144EC()));

    auto* info = mActor->getPlayerRideInfo();
    ksys::act::Actor* ride_actor = nullptr;
    if (!info->_18.isAccessingSpecifiedProcUnsafe(info->mActor))
        ride_actor = sead::DynamicCast<ksys::act::Actor>(info->_18.getProc(nullptr, info->mActor));
    if (auto* actor = sead::DynamicCast<ksys::act::Actor>(ride_actor)) {
        sub_7100E7F25C(mActor->getASList(), actor, 0, 0, -1);
        mActor->getASList()->x_6(10, 0, _40);
    }
}

}  // namespace uking::action
