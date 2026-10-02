#include "Game/AI/AI/aiDemoRootAI.h"

namespace uking::ai {

DemoRootAI::DemoRootAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DemoRootAI::~DemoRootAI() {
    for (auto*& child : _38) {
        if (child) {
            delete child;
            child = nullptr;
        }
    }
    _38.freeBuffer();
}

bool DemoRootAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DemoRootAI::enter_(ksys::act::ai::InlineParamPack* params) {
    _48 &= 4;
    _4a = 0;
    setFinished();
    sub_7100D62598();
}

void DemoRootAI::calc_() {
    sub_7100D62598();
    for (auto* child : _38) {
        if (child)
            child->calc();
    }
    _4a = _48;
    _48 = 0;
}

void DemoRootAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DemoRootAI::loadParams_() {}

}  // namespace uking::ai
