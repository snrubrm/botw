#include "Game/Actor/Area/Action/actionAreaActionBase.h"

namespace uking::action {

AreaActionBase::AreaActionBase(const InitArg& arg) : ksys::act::ai::Action(arg), ActorObserver(this) {}

void AreaActionBase::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100E28168();
}

void AreaActionBase::calc_() {
    sub_7100E282AC();
}

bool AreaActionBase::handleMessage_(const ksys::Message* message) {
    return sub_7100E289C0(message);
}

}  // namespace uking::action
