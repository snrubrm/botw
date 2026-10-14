#include "Game/Actor/AI/aiAddViewTarget.h"
#include "Game/Actor/aiUnk_71005D6D10.h"

namespace uking::ai {

AddViewTarget::AddViewTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AddViewTarget::~AddViewTarget() = default;

bool AddViewTarget::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool AddViewTarget::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool AddViewTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AddViewTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("行動", params);
}

void AddViewTarget::calc_() {
    sead::Vector3f pos;
    m34(&pos);
    sub_71005DB068(mActor, pos);
}

void AddViewTarget::leave_() {
    sub_71005DB3EC(mActor);
}

void AddViewTarget::loadParams_() {}

}  // namespace uking::ai
