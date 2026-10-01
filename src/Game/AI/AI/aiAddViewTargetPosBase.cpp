#include "Game/AI/AI/aiAddViewTargetPosBase.h"

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

void AddViewTargetPosBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AddViewTargetPosBase::loadParams_() {}

}  // namespace uking::ai
