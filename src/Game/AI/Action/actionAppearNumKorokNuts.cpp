#include "Game/AI/Action/actionAppearNumKorokNuts.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

AppearNumKorokNuts::AppearNumKorokNuts(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AppearNumKorokNuts::~AppearNumKorokNuts() = default;

bool AppearNumKorokNuts::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool AppearNumKorokNuts::oneShot_() {
    return ui::sub_7100A96DDC(false);
}

void AppearNumKorokNuts::loadParams_() {}

}  // namespace uking::action
