#include "Game/AI/Action/actionSideWalkBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SideWalkBase::SideWalkBase(const InitArg& arg) : MoveBase(arg) {}

SideWalkBase::~SideWalkBase() = default;

bool SideWalkBase::init_(sead::Heap* heap) {
    return MoveBase::init_(heap);
}

void SideWalkBase::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveBase::enter_(params);
}

void SideWalkBase::leave_() {
    MoveBase::leave_();
}

void SideWalkBase::loadParams_() {
    MoveBase::loadParams_();
    getStaticParam(&mLeftMove_s, "LeftMove");
}

void SideWalkBase::calc_() {
    MoveBase::calc_();
}

void SideWalkBase::m32(sead::Vector3f* dir) {
    if (!dir)
        return;
    mActor->getMtx().getBase(*dir, 0);
    dir->normalize();
    if (!*mLeftMove_s)
        dir->negate();
}

}  // namespace uking::action
