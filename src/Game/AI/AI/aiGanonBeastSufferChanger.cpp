#include "Game/AI/AI/aiGanonBeastSufferChanger.h"
#include "Game/AI/aiUnk_710070284C.h"

namespace uking::ai {

GanonBeastSufferChanger::GanonBeastSufferChanger(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBeastSufferChanger::~GanonBeastSufferChanger() = default;

bool GanonBeastSufferChanger::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonBeastSufferChanger::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsWeakPointAppearMode_a) {
        changeChild("弱点露出");
        *mIsWeakPointAppearMode_a = true;
    } else {
        const s32 stage = sub_710070284C(mActor);
        const s32* time_s;
        switch (stage) {
        case 0:
            time_s = mWeakPoint1Time_s;
            break;
        case 1:
            time_s = mWeakPoint2Time_s;
            break;
        case 2:
            time_s = mWeakPoint3Time_s;
            break;
        default:
            time_s = mWeakPoint4Time_s;
            break;
        }
        const s32 time = *time_s;
        _d5 = time >= 0;
        _d0 = time;
        if (time < 0)
            changeChild("無敵モード");
        else
            changeChild("通常");
        *mIsWeakPointAppearMode_a = false;
    }
}

void GanonBeastSufferChanger::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonBeastSufferChanger::loadParams_() {
    getStaticParam(&mWeakPoint1Time_s, "WeakPoint1Time");
    getStaticParam(&mWeakPoint2Time_s, "WeakPoint2Time");
    getStaticParam(&mWeakPoint3Time_s, "WeakPoint3Time");
    getStaticParam(&mWeakPoint4Time_s, "WeakPoint4Time");
    getStaticParam(&mCloseOption_s, "CloseOption");
    getStaticParam(&mTimer_s, "Timer");
    getStaticParam(&mmstxtName_s, "mstxtName");
    getStaticParam(&mlabelName_s, "labelName");
    getStaticParam(&mlabelName2_s, "labelName2");
    getStaticParam(&mlabelName3_s, "labelName3");
    getAITreeVariable(&mIsWeakPointAppearMode_a, "IsWeakPointAppearMode");
    getAITreeVariable(&mSufferChangeStopCounter_a, "SufferChangeStopCounter");
    getAITreeVariable(&mSimpleDialogUnit_a, "SimpleDialogUnit");
    getAITreeVariable(&mInBeastGanonVoiceSequence_a, "InBeastGanonVoiceSequence");
}

bool GanonBeastSufferChanger::isFailed() const {
    if (ActionBase::isFailed())
        return true;
    if (isCurrentChild("通常"))
        return getCurrentChild()->isFailed();
    return false;
}

bool GanonBeastSufferChanger::isFinished() const {
    if (ActionBase::isFinished())
        return true;
    if (isCurrentChild("通常"))
        return getCurrentChild()->isFinished();
    return false;
}

}  // namespace uking::ai
