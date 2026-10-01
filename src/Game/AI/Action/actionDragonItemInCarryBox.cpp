#include "Game/AI/Action/actionDragonItemInCarryBox.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

DragonItemInCarryBox::DragonItemInCarryBox(const InitArg& arg) : InCarryBox(arg) {}

DragonItemInCarryBox::~DragonItemInCarryBox() = default;

bool DragonItemInCarryBox::init_(sead::Heap* heap) {
    return InCarryBox::init_(heap);
}

void DragonItemInCarryBox::enter_(ksys::act::ai::InlineParamPack* params) {
    InCarryBox::enter_(params);
}

void DragonItemInCarryBox::leave_() {
    InCarryBox::leave_();
}

void DragonItemInCarryBox::loadParams_() {
    InCarryBox::loadParams_();
    getAITreeVariable(&mIsInsideObserverArea_a, "IsInsideObserverArea");
}

void DragonItemInCarryBox::calc_() {
    InCarryBox::calc_();
    mActor->get689() = true;
}

bool DragonItemInCarryBox::handleMessage_(const ksys::Message& message) {
    if (message.getType().value != 0x3000009)
        return false;
    *mIsInsideObserverArea_a = true;
    return true;
}

}  // namespace uking::action
