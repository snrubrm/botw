#pragma once

#include "Game/AI/AI/aiGolemRootBase.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "Game/AI/aiUnk_7102451120.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

// vtable 0x71023f5460: damage callback (functions in the GolemRoot TU); placeholder name.
class Unk_71023f5460 : public dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_71023f5460, dmg::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    f32 _24;
};

// Unnamed helper object of GolemRoot (no vtable or constructor of its own; its non-virtual functions
// are at 0x71003ffbf0 / 0x71003ffd3c, before GolemRoot's constructor). init_ fills it with the actor,
// GolemClimbedTime, ClimbFinishTime and StandContactHeight. Placeholder name = first function address.
struct Unk_71003ffbf0 {
    void sub_71003FFBF0();
    bool sub_71003FFD3C();

    ksys::act::Actor* _0 = nullptr;
    u32 _8 = 0;
    float* _10 = nullptr;
    const int* _18 = nullptr;
    const float* _20 = nullptr;
};

class GolemRoot : public GolemRootBase {
    SEAD_RTTI_OVERRIDE(GolemRoot, GolemRootBase)
public:
    explicit GolemRoot(const InitArg& arg);
    ~GolemRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    void sub_710040007C();

protected:
    // static_param at offset 0x310
    const int* mClimbFinishTime_s{};
    // static_param at offset 0x318
    const float* mStandContactHeight_s{};
    // static_param at offset 0x320
    const bool* mIsBreakContactTree_s{};
    // map_unit_param at offset 0x328
    sead::SafeString mGolemWeakPointLocation_m{};
    // map_unit_param at offset 0x338
    sead::SafeString mGolemSleepType_m{};
    // map_unit_param at offset 0x348
    sead::SafeString mGolemWeakPointActor_m{};
    // aitree_variable at offset 0x358
    float* mGolemClimbedTime_a{};
    Unk_71003ffbf0 _360;
    Unk_71023f54b0 _388{mActor, 0x80000aa};
    Unk_7102451120 _3a0;
    Unk_71023f5460 _3b0;
};
KSYS_CHECK_SIZE_NX150(GolemRoot, 0x3d8);

}  // namespace uking::ai
