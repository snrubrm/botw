#include "Game/AI/AI/aiGanonBeastSufferChanger.h"
#include "Game/AI/aiUnk_710070284C.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

GanonBeastSufferChanger::GanonBeastSufferChanger(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBeastSufferChanger::~GanonBeastSufferChanger() = default;

bool GanonBeastSufferChanger::init_(sead::Heap* heap) {
    _c8.acquire(heap, static_cast<Unk_71025afb58**>(mSimpleDialogUnit_a));
    _d4 = false;
    return true;
}

void GanonBeastSufferChanger::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsWeakPointAppearMode_a) {
        changeChild("弱点露出");
        *mIsWeakPointAppearMode_a = true;
    } else {
        const int* time_ptr;
        switch (sub_710070284C(mActor)) {
        case 0:
            time_ptr = mWeakPoint1Time_s;
            break;
        case 1:
            time_ptr = mWeakPoint2Time_s;
            break;
        case 2:
            time_ptr = mWeakPoint3Time_s;
            break;
        default:
            time_ptr = mWeakPoint4Time_s;
            break;
        }
        const int time = *time_ptr;
        _d0 = time;
        _d5 = time >= 0;
        if (time >= 0)
            changeChild("通常");
        else
            changeChild("無敵モード");
        *mIsWeakPointAppearMode_a = false;
    }
}

void GanonBeastSufferChanger::leave_() {
    ksys::act::ai::Ai::leave_();
}

// NON_MATCHING: the original keeps `this + 0x38` (&mSufferChangeStopCounter_a) in a callee-saved register
// from before the preceding call (frame 0x40 instead of 0x30)
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
