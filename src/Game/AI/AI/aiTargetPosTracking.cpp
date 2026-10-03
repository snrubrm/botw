#include "Game/AI/AI/aiTargetPosTracking.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/System/VFR.h"

namespace uking::ai {

TargetPosTracking::TargetPosTracking(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetPosTracking::~TargetPosTracking() = default;

bool TargetPosTracking::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetPosTracking::enter_(ksys::act::ai::InlineParamPack* params) {
    _5c = false;
    _50 = *mParams.mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_50, "TargetPos", -1);
    changeChild("追跡行動", &pack);
}

// NON_MATCHING: the TargetPos pointer load is hoisted above the speed branch here; register
// allocation of the difference vector
void TargetPosTracking::calc_() {
    if (*mParams.mIsStoppedByJustAvoid_s) {
        if (_5c)
            return;
        if (sub_710072B7C4())
            _5c = true;
    }

    const f32 speed = *mParams.mTrackSpeed_s;
    if (speed < 0.0f) {
        _50 = *mParams.mTargetPos_d;
    } else {
        const sead::Vector3f& target = *mParams.mTargetPos_d;
        const f32 step = speed * ksys::VFR::instance()->getDeltaFrame();
        const sead::Vector3f diff = target - _50;
        const f32 len = diff.length();
        if (len <= step)
            _50.set(target);
        else
            _50 += diff * (1.0f / len) * step;
    }
    getCurrentChild()->setDynamicParam(_50, "TargetPos");
}

void TargetPosTracking::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetPosTracking::loadParams_() {
    getStaticParam(&mParams.mTrackSpeed_s, "TrackSpeed");
    getStaticParam(&mParams.mIsStoppedByJustAvoid_s, "IsStoppedByJustAvoid");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

bool TargetPosTracking::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

void TargetPosTracking::m34() {}

}  // namespace uking::ai
