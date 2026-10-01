#include "Game/AI/AI/aiAddViewTargetPosBase.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

AddViewTargetPosBase::AddViewTargetPosBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AddViewTargetPosBase::~AddViewTargetPosBase() = default;

bool AddViewTargetPosBase::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool AddViewTargetPosBase::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool AddViewTargetPosBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AddViewTargetPosBase::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("行動", params);
}

void AddViewTargetPosBase::calc_() {
    sead::Vector3f pos;
    m34(&pos);
    sub_71005DB068(mActor, pos);
}

void AddViewTargetPosBase::leave_() {
    sub_71005DB3EC(mActor);
}

void AddViewTargetPosBase::loadParams_() {}

}  // namespace uking::ai
