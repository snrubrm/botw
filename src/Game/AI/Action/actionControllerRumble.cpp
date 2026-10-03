#include "Game/AI/Action/actionControllerRumble.h"
#include "Game/gameRumble.h"

namespace uking::action {

ControllerRumble::ControllerRumble(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void ControllerRumble::enter_(ksys::act::ai::InlineParamPack* params) {
    setFinished();
    _30 = *mPattern_s;
    _34 = *mCount_d > 1 ? *mCount_d : 1;
    if (auto* rumble = Rumble::instance())
        rumble->sub_7100897FE4(_30, _34);
}

void ControllerRumble::loadParams_() {
    getStaticParam(&mPattern_s, "Pattern");
    getDynamicParam_2(&mCount_d, "Count");
}

}  // namespace uking::action
