#include "Game/AI/Action/actionForkGanonBeastWeakPoint.h"
#include "Game/AI/aiUnk_71025b2d88.h"

namespace uking::action {

ForkGanonBeastWeakPoint::ForkGanonBeastWeakPoint(const InitArg& arg) : Fork(arg) {}

ForkGanonBeastWeakPoint::~ForkGanonBeastWeakPoint() = default;

bool ForkGanonBeastWeakPoint::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkGanonBeastWeakPoint::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
    _50 = 0;
    // unused in the original too (constructed and destroyed around the loop)
    sead::FixedSafeString<64> unused_name;
    auto* weak_points =
        sead::DynamicCast<Unk_71025b2d88>(*static_cast<Unk_71025afb58**>(mWeakPointActiveFlag_a));
    if (weak_points) {
        for (s32 i = 0; i < 18; ++i) {
            if ((1u << i) & weak_points->mFlags)
                m32(i, *mTargetSlotIdx_s);
        }
    }
}

void ForkGanonBeastWeakPoint::leave_() {
    Fork::leave_();
}

void ForkGanonBeastWeakPoint::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mTargetSlotIdx_s, "TargetSlotIdx");
    getAITreeVariable(&mIsWeakPointAppearMode_a, "IsWeakPointAppearMode");
    getAITreeVariable(&mWeakPointActiveFlag_a, "WeakPointActiveFlag");
    getAITreeVariable(&mWeakPointAliveFlag_a, "WeakPointAliveFlag");
}

void ForkGanonBeastWeakPoint::calc_() {
    Fork::calc_();
    auto* weak_points =
        sead::DynamicCast<Unk_71025b2d88>(*static_cast<Unk_71025afb58**>(mWeakPointActiveFlag_a));
    if (weak_points) {
        for (s32 i = 0; i < 18; ++i) {
            if (!((1u << i) & weak_points->mFlags))
                continue;
            if (!isFinishedAS(1, i + *mTargetSlotIdx_s))
                return;
        }
    }
    setEndState();
}

void ForkGanonBeastWeakPoint::m32(s32 point, s32 target_slot) {}

}  // namespace uking::action
