#include "Game/AI/AI/aiRopeRoot.h"
#include "Game/Actor/actRope.h"

namespace uking::ai {

RopeRoot::RopeRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RopeRoot::~RopeRoot() = default;

bool RopeRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RopeRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _58 = sead::DynamicCast<act::Rope>(mActor);
    _48.acquire(_58, false);
    changeChild("通常", nullptr);
}

void RopeRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RopeRoot::loadParams_() {
    getMapUnitParam(&mRopeFlag_m, "RopeFlag");
    getMapUnitParam(&mRopeAlwaysUpdateRigidParam_m, "RopeAlwaysUpdateRigidParam");
}

}  // namespace uking::ai
