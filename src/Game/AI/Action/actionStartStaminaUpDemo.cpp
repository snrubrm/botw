#include "Game/AI/Action/actionStartStaminaUpDemo.h"
#include "Game/AI/aiUnk_710073BB28.h"

namespace uking::action {

StartStaminaUpDemo::StartStaminaUpDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StartStaminaUpDemo::~StartStaminaUpDemo() = default;

bool StartStaminaUpDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StartStaminaUpDemo::loadParams_() {}

bool StartStaminaUpDemo::oneShot_() {
    sub_710073BB28(true, false);
    return true;
}

}  // namespace uking::action
