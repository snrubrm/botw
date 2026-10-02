#include "Game/AI/AI/aiStalEnemyRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

StalEnemyRoot::StalEnemyRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalEnemyRoot::~StalEnemyRoot() = default;

bool StalEnemyRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalEnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StalEnemyRoot::leave_() {
    sub_71005DA114(mActor, &_38);
}

void StalEnemyRoot::loadParams_() {
    getStaticParam(&mDeadCount_s, "DeadCount");
    getStaticParam(&mSearchFrame_s, "SearchFrame");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mOutOfWaterOffset_s, "OutOfWaterOffset");
    getStaticParam(&mDeadCheckFrame_s, "DeadCheckFrame");
    getStaticParam(&mSpreadDist_s, "SpreadDist");
    getStaticParam(&mSmallSpreadDist_s, "SmallSpreadDist");
    getStaticParam(&mSearchDistXZ_s, "SearchDistXZ");
    getStaticParam(&mSearchDistY_s, "SearchDistY");
    getStaticParam(&mFallHeight_s, "FallHeight");
    getMapUnitParam(&mIsCreateStalPart_m, "IsCreateStalPart");
    getAITreeVariable(&mIsStopFallCheck_a, "IsStopFallCheck");
    getAITreeVariable(&mStalEnemyUnit_a, "StalEnemyUnit");
}

bool StalEnemyRoot::m34() {
    if (_2e8._8.isOnBit(0))
        return false;
    return sub_71005D6E28(mActor);
}

void StalEnemyRoot::m35() {}

bool StalEnemyRoot::m36() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        return true;
    return getCurrentChild()->isChangeable();
}

}  // namespace uking::ai
