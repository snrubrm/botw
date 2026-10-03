#include "Game/AI/Action/actionForceSetCameraPos.h"

namespace uking::action {

forceSetCameraPos::forceSetCameraPos(const InitArg& arg) : ksys::act::ai::Action(arg) {}

forceSetCameraPos::~forceSetCameraPos() = default;

bool forceSetCameraPos::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void forceSetCameraPos::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void forceSetCameraPos::leave_() {
    ksys::act::ai::Action::leave_();
}

void forceSetCameraPos::loadParams_() {}

void forceSetCameraPos::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
