#include "Game/AI/Action/actionKokkoCreateDropBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

KokkoCreateDropBase::KokkoCreateDropBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KokkoCreateDropBase::~KokkoCreateDropBase() = default;

bool KokkoCreateDropBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void KokkoCreateDropBase::enter_(ksys::act::ai::InlineParamPack* params) {
    if (m32()) {
        mActor->createDrops(1, 0);
        mActor->sub_71011D49C8();
    }
    mFlags.set(Flag::Changeable);
}

void KokkoCreateDropBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void KokkoCreateDropBase::loadParams_() {}

void KokkoCreateDropBase::calc_() {
    ksys::act::ai::Action::calc_();
}

bool KokkoCreateDropBase::m32() {
    return true;
}

}  // namespace uking::action
