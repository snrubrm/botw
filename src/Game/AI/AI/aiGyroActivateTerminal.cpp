#include "Game/AI/AI/aiGyroActivateTerminal.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

GyroActivateTerminal::GyroActivateTerminal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GyroActivateTerminal::~GyroActivateTerminal() = default;

bool GyroActivateTerminal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GyroActivateTerminal::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _38.x();
    ksys::act::enableAttClient(actor, "BootPStop");
    _78 = false;
    changeChild("待機");
    _78 = false;
}

void GyroActivateTerminal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GyroActivateTerminal::loadParams_() {}

bool GyroActivateTerminal::handleMessage_(const ksys::Message& message) {
    if (isCurrentChild("待機") && _38.m2(message))
        return true;
    return false;
}

}  // namespace uking::ai
