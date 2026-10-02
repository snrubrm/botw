#include "Game/AI/AI/aiKeeseSwarmRoam.h"

namespace uking::ai {

KeeseSwarmRoam::KeeseSwarmRoam(const InitArg& arg) : CircleMove(arg) {}

KeeseSwarmRoam::~KeeseSwarmRoam() = default;

bool KeeseSwarmRoam::init_(sead::Heap* heap) {
    if (!CircleMove::init_(heap))
        return false;
    _68.fill(0);
    return true;
}

void KeeseSwarmRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    CircleMove::enter_(params);
}

void KeeseSwarmRoam::leave_() {
    CircleMove::leave_();
}

void KeeseSwarmRoam::loadParams_() {
    CircleMove::loadParams_();
    getDynamicParam(&mCentralPos_d, "CentralPos");
}

void KeeseSwarmRoam::m34(sead::Vector3f* out) {
    if (out)
        out->set(*mCentralPos_d);
}

}  // namespace uking::ai
