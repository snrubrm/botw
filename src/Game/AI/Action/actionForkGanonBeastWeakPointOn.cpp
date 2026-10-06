#include "Game/AI/Action/actionForkGanonBeastWeakPointOn.h"
#include "Game/AI/aiUnk_71025b2d88.h"

// Declaration only; original global name retained, source namespace unknown.
void ganonBeastWeakPointSetOn(ksys::act::Actor* actor, s32 point, s32 target_slot);

// 0x7100703c18 (declaration only, 1288 B): picks (randomly, depending on the actor's position and a state) the weak
// points to activate from `alive_flags` and writes them to `active_flags`.
void sub_7100703C18(u32* active_flags, ksys::act::Actor* actor, const u32* alive_flags);

namespace uking::action {

ForkGanonBeastWeakPointOn::ForkGanonBeastWeakPointOn(const InitArg& arg)
    : ForkGanonBeastWeakPoint(arg) {}

ForkGanonBeastWeakPointOn::~ForkGanonBeastWeakPointOn() = default;

bool ForkGanonBeastWeakPointOn::init_(sead::Heap* heap) {
    return ForkGanonBeastWeakPoint::init_(heap);
}

void ForkGanonBeastWeakPointOn::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* active =
        sead::DynamicCast<Unk_71025b2d88>(*static_cast<Unk_71025afb58**>(mWeakPointActiveFlag_a));
    if (active && active->mFlags == 0) {
        auto* alive = sead::DynamicCast<Unk_71025b2d88>(
            *static_cast<Unk_71025afb58**>(mWeakPointAliveFlag_a));
        if (alive)
            sub_7100703C18(&active->mFlags, mActor, &alive->mFlags);
    }
    ForkGanonBeastWeakPoint::enter_(params);
    *mIsWeakPointAppearMode_a = true;
}

void ForkGanonBeastWeakPointOn::leave_() {
    ForkGanonBeastWeakPoint::leave_();
}

void ForkGanonBeastWeakPointOn::loadParams_() {
    ForkGanonBeastWeakPoint::loadParams_();
}

void ForkGanonBeastWeakPointOn::calc_() {
    ForkGanonBeastWeakPoint::calc_();
}

void ForkGanonBeastWeakPointOn::m32(s32 point, s32 target_slot) {
    ganonBeastWeakPointSetOn(mActor, point, target_slot);
}

}  // namespace uking::action
