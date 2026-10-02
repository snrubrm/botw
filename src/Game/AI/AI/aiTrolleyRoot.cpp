#include "Game/AI/AI/aiTrolleyRoot.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"

namespace uking::ai {

TrolleyRoot::TrolleyRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TrolleyRoot::~TrolleyRoot() {
    if (_d0) {
        ksys::phys::Constraint::destroy(_d0);
        _d0 = nullptr;
    }
}

bool TrolleyRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TrolleyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("転がり");
    if (_d0)
        _d0->sub_7100F69FF0();
}

void TrolleyRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TrolleyRoot::loadParams_() {
    getStaticParam(&mNearGoalDist_s, "NearGoalDist");
    getStaticParam(&mNearGoalLimitSpd_s, "NearGoalLimitSpd");
    getStaticParam(&mNearGoalReduceRate_s, "NearGoalReduceRate");
}

bool TrolleyRoot::handleMessage_(const ksys::Message& message) {
    if (!_70._30)
        _70.m2(message);
    return false;
}

}  // namespace uking::ai
