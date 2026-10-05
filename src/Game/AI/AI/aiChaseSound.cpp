#include "Game/AI/AI/aiChaseSound.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/Physics/System/physRayCastForRequest.h"

bool sub_71005E2068(ksys::act::Actor* actor);

namespace uking::ai {

ChaseSound::ChaseSound(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ChaseSound::~ChaseSound() = default;

void ChaseSound::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ChaseSound::leave_() {
    if (_78) {
        _78->release();
        _78 = nullptr;
    }
}

// NON_MATCHING: Temporary string storage uses a larger stack frame.
void ChaseSound::calc_() {
    if (isCurrentChild("見まわし")) {
        sub_71005DB3EC(mActor);
    } else {
        const sead::Vector3f target = _80;
        if (*mParams.mUseViewPointSimpleOffset_s)
            sub_71005DB1D8(mActor, target);
        else
            sub_71005DB068(mActor, target);
    }
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("回転")) {
            if (!sub_7100345C2C())
                setFailed();
        } else if (isCurrentChild("見まわし")) {
            sub_7100345C2C();
        } else if (getCurrentChild()->isFinished()) {
            setFinished();
        } else {
            setFailed();
        }
    }
    if (getCurrentChild()->isChangeable() && !isCurrentChild("回転") &&
        !isCurrentChild("見まわし") && sub_71005E2068(mActor)) {
        setFailed();
    }
    sub_7100346114();
    getCurrentChild()->setDynamicParam(_80, "TargetPos");
}

void ChaseSound::loadParams_() {
    getStaticParam(&mParams.mTargetUpdateIntervalMin_s, "TargetUpdateIntervalMin");
    getStaticParam(&mParams.mTargetUpdateIntervalMax_s, "TargetUpdateIntervalMax");
    getStaticParam(&mParams.mNearDist_s, "NearDist");
    getStaticParam(&mParams.mTurnDir_s, "TurnDir");
    getStaticParam(&mParams.mUseViewPointSimpleOffset_s, "UseViewPointSimpleOffset");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
