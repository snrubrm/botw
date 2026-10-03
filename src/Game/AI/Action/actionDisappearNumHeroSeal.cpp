#include "Game/AI/Action/actionDisappearNumHeroSeal.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

DisappearNumHeroSeal::DisappearNumHeroSeal(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DisappearNumHeroSeal::~DisappearNumHeroSeal() = default;

bool DisappearNumHeroSeal::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool DisappearNumHeroSeal::oneShot_() {
    return ui::sub_7100A97B14();
}

void DisappearNumHeroSeal::loadParams_() {}

}  // namespace uking::action
