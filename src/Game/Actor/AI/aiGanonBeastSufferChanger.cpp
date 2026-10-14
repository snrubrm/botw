#include "Game/Actor/AI/aiGanonBeastSufferChanger.h"
#include "Game/Actor/aiUnk_710070284C.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/Timer.h"
#include <random/seadGlobalRandom.h>

namespace uking::ai {

GanonBeastSufferChanger::GanonBeastSufferChanger(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBeastSufferChanger::~GanonBeastSufferChanger() = default;

bool GanonBeastSufferChanger::init_(sead::Heap* heap) {
    _c8.acquire(heap, static_cast<Unk_71025afb58**>(mParams.mSimpleDialogUnit_a));
    _d4 = 0;
    return true;
}

void GanonBeastSufferChanger::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mParams.mIsWeakPointAppearMode_a) {
        changeChild("弱点露出");
        *mParams.mIsWeakPointAppearMode_a = true;
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
        *mParams.mIsWeakPointAppearMode_a = false;
    }
}

// NON_MATCHING: block layout of the third label test; the dialog data pointer becomes a csel (same as
// GanonBeastFirstMessage::sub_7100624048).
void GanonBeastSufferChanger::calc_() {
    if (*mParams.mSufferChangeStopCounter_a <= 0 && _d5 && isCurrentChild("通常") && _d0 >= 0.0f)
        ksys::Timer::update(&_d0, -1.0f);

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("弱点露出")) {
            if ((_d4 & 7) == 7)
                _d4 = 0;

            // Pick one of the labels that has not been used yet.
            s32 index = 0;
            u32 count = 1;
            for (s32 i = 0; i < 3; ++i) {
                if (_d4 & (1 << i))
                    continue;
                if (sead::GlobalRandom::instance()->getU32(count) == 0)
                    index = i;
                ++count;
            }
            _d4 |= 1 << index;

            const sead::SafeString* label;
            if (index == 1)
                label = &mlabelName2_s;
            else if (index == 2)
                label = &mlabelName3_s;
            else
                label = &mlabelName_s;

            if (!label->isEmpty()) {
                Unk_71025b2aa8Data::Request request;
                request._0 = &mmstxtName_s;
                request._8 = label;
                request._10 = *mCloseOption_s;
                request._14 = 1;
                request._18 = *mTimer_s;
                if (_c8._0) {
                    auto* unit = sead::DynamicCast<Unk_71025b2aa8>(*_c8._0);
                    if (unit && unit->mRefCount >= 1)
                        _c8.getData()->sub_7100721DE4(&request);
                }
            }
        }
    } else {
        if (!child->isChangeable())
            return;

        if (isCurrentChild("通常")) {
            if (*mParams.mInBeastGanonVoiceSequence_a || !_d5 || !(_d0 <= 0.0f))
                return;
            changeChild("弱点露出");
            *mParams.mIsWeakPointAppearMode_a = true;
            return;
        }

        if (!isCurrentChild("弱点露出") || *mParams.mIsWeakPointAppearMode_a)
            return;
    }

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
    _d5 = time >= 0;
    _d0 = time;
    if (time >= 0)
        changeChild("通常");
    else
        changeChild("無敵モード");
    *mParams.mIsWeakPointAppearMode_a = false;
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
    getAITreeVariable(&mParams.mIsWeakPointAppearMode_a, "IsWeakPointAppearMode");
    getAITreeVariable(&mParams.mSufferChangeStopCounter_a, "SufferChangeStopCounter");
    getAITreeVariable(&mParams.mSimpleDialogUnit_a, "SimpleDialogUnit");
    getAITreeVariable(&mParams.mInBeastGanonVoiceSequence_a, "InBeastGanonVoiceSequence");
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
