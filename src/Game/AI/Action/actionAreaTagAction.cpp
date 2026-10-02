#include "Game/AI/Action/actionAreaTagAction.h"

namespace uking::action {

AreaTagAction::AreaTagAction(const InitArg& arg) : ksys::act::ai::Action(arg), ActorObserver(this) {}

void AreaTagAction::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100E28168();
}

void AreaTagAction::calc_() {
    sub_7100E282AC();
}

bool AreaTagAction::handleMessage_(const ksys::Message& message) {
    return sub_7100E289C0(&message);
}

}  // namespace uking::action
