#include "Game/AI/AI/aiBeeSwarmRoot.h"

namespace uking::ai {

BeeSwarmRoot::BeeSwarmRoot(const InitArg& arg) : SwarmRoot(arg) {}

BeeSwarmRoot::~BeeSwarmRoot() = default;

bool BeeSwarmRoot::init_(sead::Heap* heap) {
    return SwarmRoot::init_(heap);
}

void BeeSwarmRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SwarmRoot::enter_(params);
}

void BeeSwarmRoot::calc_() {
    SwarmRoot::calc_();
}

void BeeSwarmRoot::leave_() {
    SwarmRoot::leave_();
}

void BeeSwarmRoot::loadParams_() {
    SwarmRoot::loadParams_();
}

bool BeeSwarmRoot::m35() {
    return SwarmRoot::m35();
}

}  // namespace uking::ai
