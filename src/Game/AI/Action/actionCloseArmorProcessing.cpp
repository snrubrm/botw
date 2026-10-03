#include "Game/AI/Action/actionCloseArmorProcessing.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

CloseArmorProcessing::CloseArmorProcessing(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CloseArmorProcessing::~CloseArmorProcessing() = default;

bool CloseArmorProcessing::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CloseArmorProcessing::enter_(ksys::act::ai::InlineParamPack* params) {
    ui::sub_7100A984C0();
}

void CloseArmorProcessing::leave_() {
    ksys::act::ai::Action::leave_();
}

void CloseArmorProcessing::loadParams_() {}

void CloseArmorProcessing::calc_() {
    if (!ui::sub_7100A98498())
        setFinished();
}

}  // namespace uking::action
