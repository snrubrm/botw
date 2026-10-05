#include "Game/AI/Action/actionAscendingCurrent.h"

namespace uking::action {

AscendingCurrent::AscendingCurrent(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AscendingCurrent::~AscendingCurrent() = default;

bool AscendingCurrent::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AscendingCurrent::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AscendingCurrent::leave_() {
    ksys::act::ai::Action::leave_();
}

void AscendingCurrent::loadParams_() {
    getStaticParam(&mWindSpeed_s, "WindSpeed");
}

void AscendingCurrent::calc_() {
    sub_71000A6F24();
    sub_71000A7354();
}

bool AscendingCurrent::hasUpdateForPreDeleteCb() {
    return true;
}

}  // namespace uking::action
