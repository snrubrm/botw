#include "Game/AI/Action/actionForkGanonBeastWeakPointCheck.h"

// Full native helper uses the signed AS slot as an animation-slot offset; namespace unknown.
void sub_7100703904(ksys::act::Actor* actor, s32 slot);

namespace uking::action {

ForkGanonBeastWeakPointCheck::ForkGanonBeastWeakPointCheck(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkGanonBeastWeakPointCheck::~ForkGanonBeastWeakPointCheck() = default;

bool ForkGanonBeastWeakPointCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkGanonBeastWeakPointCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    _200 = *mIsWeakPointAppearMode_a;
    if (isRootAiParamINot5())
        sub_7100703904(mActor, 0);
    if (!mDamageCallback.mDamageManager)
        setDamageCallbackTiming(mActor, 0, &mDamageCallback);
    if (!mLastWeakPointDamageCallback.mDamageManager)
        setDamageCallbackTiming(mActor, 5, &mLastWeakPointDamageCallback);
    _1f8 = 0.0f;
    _1fc = 0.0f;
    _201 = false;
}

void ForkGanonBeastWeakPointCheck::leave_() {
    if (mDamageCallback.mDamageManager)
        sub_71005DA114(mActor, &mDamageCallback);
    if (mLastWeakPointDamageCallback.mDamageManager)
        sub_71005DA114(mActor, &mLastWeakPointDamageCallback);
}

void ForkGanonBeastWeakPointCheck::loadParams_() {
    getStaticParam(&mASSlot_s, "ASSlot");
    getStaticParam(&mLastWeakCounter_s, "LastWeakCounter");
    getStaticParam(&mLastWeakSlowEndSafeTime_s, "LastWeakSlowEndSafeTime");
    getAITreeVariable(&mLastDamageWeakPointIdx_a, "LastDamageWeakPointIdx");
    getAITreeVariable(&mIsWeakPointAppearMode_a, "IsWeakPointAppearMode");
    getAITreeVariable(&mWeakPointActiveFlag_a, "WeakPointActiveFlag");
    getAITreeVariable(&mWeakPointAliveFlag_a, "WeakPointAliveFlag");
    getAITreeVariable(&mGanonBeastWeakPointXLinkHandle_a, "GanonBeastWeakPointXLinkHandle");
    getAITreeVariable(&mWeakPointCounter_a, "WeakPointCounter");
}

void ForkGanonBeastWeakPointCheck::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
