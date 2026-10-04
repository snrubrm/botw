#include "Game/AI/Action/actionHorseManeGrabbedAction.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseManeGrabbedAction::HorseManeGrabbedAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseManeGrabbedAction::~HorseManeGrabbedAction() = default;

bool HorseManeGrabbedAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseManeGrabbedAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseManeGrabbedAction::leave_() {
    mActor->sub_71011DA834(&_20);
    for (s32 i = 0; i < 12; ++i)
        _20.getEntry(i).reset();
}

void HorseManeGrabbedAction::loadParams_() {}

void HorseManeGrabbedAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
