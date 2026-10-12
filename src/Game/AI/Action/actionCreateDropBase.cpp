#include "Game/AI/Action/actionCreateDropBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

CreateDropBase::CreateDropBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CreateDropBase::~CreateDropBase() = default;

bool CreateDropBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CreateDropBase::enter_(ksys::act::ai::InlineParamPack* params) {
    if (m32()) {
        mActor->createDrops(1, 0);
        mActor->sub_71011D49C8();
    }
    mFlags.set(Flag::Changeable);
}

void CreateDropBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void CreateDropBase::loadParams_() {}

void CreateDropBase::calc_() {
    ksys::act::ai::Action::calc_();
}

bool CreateDropBase::m32() {
    return true;
}

}  // namespace uking::action
