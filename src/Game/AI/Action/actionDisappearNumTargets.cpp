#include "Game/AI/Action/actionDisappearNumTargets.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

DisappearNumTargets::DisappearNumTargets(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DisappearNumTargets::~DisappearNumTargets() = default;

bool DisappearNumTargets::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool DisappearNumTargets::oneShot_() {
    ui::sub_7100A99A08();
    return ksys::act::ai::Action::oneShot_();
}

void DisappearNumTargets::loadParams_() {}

}  // namespace uking::action
