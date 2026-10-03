#include "Game/AI/Action/actionSystemSetWindAction.h"
#include "KingSystem/World/worldManager.h"

namespace uking::action {

SystemSetWindAction::SystemSetWindAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool SystemSetWindAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SystemSetWindAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SystemSetWindAction::leave_() {
    ksys::world::Manager::instance()->resetManualWind();
}

void SystemSetWindAction::loadParams_() {
    getDynamicParam(&mWindDirX_d, "WindDirX");
    getDynamicParam(&mWindDirY_d, "WindDirY");
    getDynamicParam(&mWindDirZ_d, "WindDirZ");
    getDynamicParam(&mWindPower_d, "WindPower");
    getDynamicParam(&mIsAutoWind_d, "IsAutoWind");
}

void SystemSetWindAction::calc_() {
    if (auto* wm = ksys::world::Manager::instance()) {
        const f32 power = *mWindPower_d;
        wm->setManualWind(false, {*mWindDirX_d, *mWindDirY_d, *mWindDirZ_d}, power);
    }
}

}  // namespace uking::action
