#include "Game/AI/Action/actionEventDoorOpenAndClose.h"

namespace uking::action {

EventDoorOpenAndClose::EventDoorOpenAndClose(const InitArg& arg) : DoorOpenAndClose(arg) {}

EventDoorOpenAndClose::~EventDoorOpenAndClose() = default;

bool EventDoorOpenAndClose::init_(sead::Heap* heap) {
    if (!DoorOpenAndClose::init_(heap))
        return false;
    *mIsOpenDoor_a = false;
    *mIsOpenToInside_a = false;
    return true;
}

void EventDoorOpenAndClose::enter_(ksys::act::ai::InlineParamPack* params) {
    DoorOpenAndClose::enter_(params);
    *mIsOpenDoor_a = *mDynIsOpen_d;
    *mIsOpenToInside_a = *mDynIsOpenToInside_d;
}

void EventDoorOpenAndClose::leave_() {
    DoorOpenAndClose::leave_();
}

void EventDoorOpenAndClose::loadParams_() {
    DoorOpenAndClose::loadParams_();
    getDynamicParam(&mDynIsOpenToInside_d, "DynIsOpenToInside");
    getDynamicParam(&mDynIsOpen_d, "DynIsOpen");
    getAITreeVariable(&mIsOpenDoor_a, "IsOpenDoor");
    getAITreeVariable(&mIsOpenToInside_a, "IsOpenToInside");
}

void EventDoorOpenAndClose::calc_() {
    DoorOpenAndClose::calc_();
}

}  // namespace uking::action
