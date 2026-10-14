#include "Game/Actor/AI/aiAddViewTargetPos.h"
#include "Game/Actor/aiUnk_71005D6D10.h"

namespace uking::ai {

AddViewTargetPos::AddViewTargetPos(const InitArg& arg) : AddViewTarget(arg) {}

AddViewTargetPos::~AddViewTargetPos() = default;

bool AddViewTargetPos::init_(sead::Heap* heap) {
    return AddViewTarget::init_(heap);
}

void AddViewTargetPos::enter_(ksys::act::ai::InlineParamPack* params) {
    AddViewTarget::enter_(params);
}

void AddViewTargetPos::calc_() {
    AddViewTarget::calc_();
}

void AddViewTargetPos::leave_() {
    AddViewTarget::leave_();
}

void AddViewTargetPos::loadParams_() {
    AddViewTarget::loadParams_();
}

void AddViewTargetPos::m34(sead::Vector3f* out) {
    *out = sub_71005D960C(mActor);
}

}  // namespace uking::ai
