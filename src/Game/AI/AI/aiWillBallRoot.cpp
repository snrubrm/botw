#include "Game/AI/AI/aiWillBallRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actUnk_71006e45c4.h"

namespace uking::ai {

WillBallRoot::WillBallRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WillBallRoot::~WillBallRoot() = default;

bool WillBallRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WillBallRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WillBallRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WillBallRoot::loadParams_() {
    getStaticParam(&mMagneLightningTime_s, "MagneLightningTime");
    getStaticParam(&mMinimizedTime_s, "MinimizedTime");
    getStaticParam(&mImmidiateLightningXZ_s, "ImmidiateLightningXZ");
    getStaticParam(&mImmidiateLightningY_s, "ImmidiateLightningY");
    getStaticParam(&mImmidiateLightningXZTarget_s, "ImmidiateLightningXZTarget");
    getStaticParam(&mImmidiateLightningYTarget_s, "ImmidiateLightningYTarget");
    getStaticParam(&mLightningTimeMinimizeDist_s, "LightningTimeMinimizeDist");
    getStaticParam(&mIsExplode_s, "IsExplode");
    getMapUnitParam(&mCount_m, "Count");
}

// NON_MATCHING: block layout only (the original shares one `return false` block between the early exits and
// branches back to it; ours duplicates it)
bool WillBallRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000007) {
        mActor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        return true;
    }

    if (isCurrentChild("待機")) {
        if (_90._30)
            return false;
        if (auto* grab = mActor->m128(); grab && grab->m2())
            return false;
        if (!_90.m2(*message))
            return false;
        if (_90._38._48 == 2 || _90._38._48 == 3) {
            _90.x();
            return false;
        }
        return true;
    }
    return _120.m2(*message);
}

}  // namespace uking::ai
