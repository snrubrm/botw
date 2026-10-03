#include "Game/AI/Action/actionAppearFullPouchInfo.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

AppearFullPouchInfo::AppearFullPouchInfo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AppearFullPouchInfo::~AppearFullPouchInfo() = default;

bool AppearFullPouchInfo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool AppearFullPouchInfo::oneShot_() {
    ui::sub_7100A95B44(mPorchItemName_d);
    return ksys::act::ai::Action::oneShot_();
}

void AppearFullPouchInfo::loadParams_() {
    getDynamicParam(&mPorchItemName_d, "PorchItemName");
}

}  // namespace uking::action
