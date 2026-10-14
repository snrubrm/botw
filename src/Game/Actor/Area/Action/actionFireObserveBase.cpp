#include "Game/Actor/Area/Action/actionFireObserveBase.h"

bool Unk_71024e5408::m15(const void* data) {
    return false;
}

namespace uking::action {

FireObserveBase::FireObserveBase(const InitArg& arg)
    : ksys::act::ai::Action(arg), Unk_71024e5408(this) {}

void FireObserveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100E28168();
}

void FireObserveBase::calc_() {
    sub_7100E282AC();
}

bool FireObserveBase::handleMessage_(const ksys::Message* message) {
    return sub_7100E289C0(message);
}

}  // namespace uking::action
