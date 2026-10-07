#include "Game/AI/Action/actionDunegonRotateWait.h"
#include "Game/AI/aiUnk_71005D6D10.h"

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
