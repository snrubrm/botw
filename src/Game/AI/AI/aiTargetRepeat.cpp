#include "Game/AI/AI/aiTargetRepeat.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

TargetRepeat::TargetRepeat(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetRepeat::~TargetRepeat() = default;

bool TargetRepeat::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetRepeat::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("行動", &pack);
}

void TargetRepeat::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (child->isFinished()) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("行動", &pack);
        } else {
            setFailed();
        }
    }
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void TargetRepeat::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetRepeat::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool TargetRepeat::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

}  // namespace uking::ai
