#include "Game/AI/Action/actionAreaFireObserveBase.h"

bool Unk_71024e5408::m15(const void* data) {
    return false;
}

namespace uking::action {

AreaFireObserveBase::AreaFireObserveBase(const InitArg& arg)
    : ksys::act::ai::Action(arg), Unk_71024e5408(this) {}

void AreaFireObserveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100E28168();
}

void AreaFireObserveBase::calc_() {
    sub_7100E282AC();
}

bool AreaFireObserveBase::handleMessage_(const ksys::Message* message) {
    return sub_7100E289C0(message);
}

}  // namespace uking::action
