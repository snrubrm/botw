#include "Game/AI/AI/aiMimicryResetCheck.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/System/VFR.h"

namespace uking::ai {

MimicryResetCheck::MimicryResetCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MimicryResetCheck::~MimicryResetCheck() = default;

bool MimicryResetCheck::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool MimicryResetCheck::isFinished() const {
    return getCurrentChild()->isFinished();
}

void MimicryResetCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("行動", params);
}

void MimicryResetCheck::calc_() {
    if (*mIsStartResetMimicry_a && *mMimicryMaterial_a >= 0) {
        if (ksys::VFR::lerp(&_50, 0.0f, *mResetRate_s, *mResetRate_s, *mResetRate_s * 0.1f)) {
            *mIsStartResetMimicry_a = false;
            *mMimicryMaterial_a = -1;
            _50 = 1.0f;
        }
        sub_71005DD27C(mActor, *mMimicryMaterial_a, _50);
    }

    if (getCurrentChild()->isFinished())
        setFinished();
    else if (getCurrentChild()->isFailed())
        setFailed();
}

void MimicryResetCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MimicryResetCheck::loadParams_() {
    getStaticParam(&mResetRate_s, "ResetRate");
    getAITreeVariable(&mMimicryMaterial_a, "MimicryMaterial");
    getAITreeVariable(&mIsStartResetMimicry_a, "IsStartResetMimicry");
}

}  // namespace uking::ai
