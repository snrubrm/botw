#include "Game/AI/Action/actionAppearNumHeroSeal.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

AppearNumHeroSeal::AppearNumHeroSeal(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AppearNumHeroSeal::~AppearNumHeroSeal() = default;

bool AppearNumHeroSeal::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool AppearNumHeroSeal::oneShot_() {
    return ui::sub_7100A976C4(*mRelicPattern_d, false);
}

void AppearNumHeroSeal::loadParams_() {
    getDynamicParam(&mRelicPattern_d, "RelicPattern");
}

}  // namespace uking::action
