#include "Game/AI/Action/actionAppearNumTargets.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

AppearNumTargets::AppearNumTargets(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AppearNumTargets::~AppearNumTargets() = default;

bool AppearNumTargets::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool AppearNumTargets::oneShot_() {
    ui::sub_7100A9991C(mGameDataIntTargetCounter_d);
    return ksys::act::ai::Action::oneShot_();
}

void AppearNumTargets::loadParams_() {
    getDynamicParam(&mGameDataIntTargetCounter_d, "GameDataIntTargetCounter");
}

}  // namespace uking::action
