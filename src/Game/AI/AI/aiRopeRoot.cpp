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

void RopeRoot::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed() || !_48.hasProc()) {
        changeChild("通常", nullptr);
        return;
    }
    if (!child->isChangeable())
        return;
    if (isCurrentChild("通常")) {
        if (_58->_955 && _58->_96c != 2)
            changeChild("切断", nullptr);
        else if (_58->_970)
            changeChild("燃え尽き", nullptr);
    } else if (isCurrentChild("切断")) {
        changeChild("通常", nullptr);
    } else if (isCurrentChild("燃え尽き")) {
        if (_58->_970)
            changeChild("燃え尽き", nullptr);
        else
            changeChild("通常", nullptr);
    }
}

void RopeRoot::loadParams_() {
    getMapUnitParam(&mRopeFlag_m, "RopeFlag");
    getMapUnitParam(&mRopeAlwaysUpdateRigidParam_m, "RopeAlwaysUpdateRigidParam");
}

}  // namespace uking::ai
