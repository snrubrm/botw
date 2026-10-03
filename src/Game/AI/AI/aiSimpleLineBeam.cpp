#include "Game/AI/AI/aiSimpleLineBeam.h"

namespace uking::ai {

SimpleLineBeam::SimpleLineBeam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SimpleLineBeam::~SimpleLineBeam() = default;

bool SimpleLineBeam::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SimpleLineBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    _a8.makeAllZero();
    changeChild("攻撃");
}

void SimpleLineBeam::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed() || !child->isChangeable())
        return;

    if (isCurrentChild("攻撃")) {
        if (_a8.isOn(4))
            changeChild("待機");
    } else if (_a8.isOn(2)) {
        changeChild("攻撃");
    }
}

void SimpleLineBeam::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SimpleLineBeam::loadParams_() {}

bool SimpleLineBeam::handleMessage_(const ksys::Message* message) {
    if (_70.m2(*message)) {
        _70.x();
        _a8.reset(2 | 4);
        _a8.set(4);
        return true;
    }
    if (_38.m2(*message)) {
        _38.x();
        _a8.reset(2 | 4);
        _a8.set(2);
        return true;
    }
    return false;
}

}  // namespace uking::ai
