#include "Game/AI/AI/aiAddViewTargetPos.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

AddViewTargetPos::AddViewTargetPos(const InitArg& arg) : AddViewTargetPosBase(arg) {}

AddViewTargetPos::~AddViewTargetPos() = default;

bool AddViewTargetPos::init_(sead::Heap* heap) {
    return AddViewTargetPosBase::init_(heap);
}

void AddViewTargetPos::enter_(ksys::act::ai::InlineParamPack* params) {
    AddViewTargetPosBase::enter_(params);
}

void AddViewTargetPos::calc_() {
    AddViewTargetPosBase::calc_();
}

void AddViewTargetPos::leave_() {
    AddViewTargetPosBase::leave_();
}

void AddViewTargetPos::loadParams_() {
    AddViewTargetPosBase::loadParams_();
}

void AddViewTargetPos::m34(sead::Vector3f* out) {
    *out = sub_71005D960C(mActor);
}

}  // namespace uking::ai
