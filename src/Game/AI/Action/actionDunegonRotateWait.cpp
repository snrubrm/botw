#include "Game/AI/Action/actionDunegonRotateWait.h"

// The original source owner is unknown; keep the declaration in the global scope.
void sub_71005DDE8C(ksys::act::Actor* actor, const sead::Vector3f* axis, s32 part_type);

namespace uking::action {

DunegonRotateWait::DunegonRotateWait(const InitArg& arg) : DungeonRotateBase(arg) {}

DunegonRotateWait::~DunegonRotateWait() = default;

bool DunegonRotateWait::init_(sead::Heap* heap) {
    return DungeonRotateBase::init_(heap);
}

void DunegonRotateWait::enter_(ksys::act::ai::InlineParamPack* params) {
    DungeonRotateBase::enter_(params);
    mFlags.set(Flag::Changeable);
}

void DunegonRotateWait::leave_() {
    DungeonRotateBase::leave_();
}

void DunegonRotateWait::loadParams_() {
    DungeonRotateBase::loadParams_();
}

void DunegonRotateWait::calc_() {
    DungeonRotateBase::calc_();
    sub_71005DDE8C(mActor, &_70, *mRemainsPartType_m);
}

}  // namespace uking::action
