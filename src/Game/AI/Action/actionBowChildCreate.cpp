#include "Game/AI/Action/actionBowChildCreate.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

BowChildCreate::BowChildCreate(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BowChildCreate::~BowChildCreate() = default;

bool BowChildCreate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BowChildCreate::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BowChildCreate::leave_() {
    mActor->sub_71011DA834(&_30);
}

void BowChildCreate::loadParams_() {
    getDynamicParam(&mID_d, "ID");
    getDynamicParam(&mParentActor_d, "ParentActor");
}

void BowChildCreate::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
