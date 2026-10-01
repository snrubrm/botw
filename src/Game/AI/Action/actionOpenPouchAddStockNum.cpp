#include "Game/AI/Action/actionOpenPouchAddStockNum.h"

namespace uking::action {

OpenPouchAddStockNum::OpenPouchAddStockNum(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenPouchAddStockNum::~OpenPouchAddStockNum() = default;

bool OpenPouchAddStockNum::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenPouchAddStockNum::enter_(ksys::act::ai::InlineParamPack* params) {
    _28 = false;
    _29 = false;
}

void OpenPouchAddStockNum::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenPouchAddStockNum::loadParams_() {
    getDynamicParam(&mType_d, "Type");
}

void OpenPouchAddStockNum::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
