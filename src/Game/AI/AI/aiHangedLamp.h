#pragma once

#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

// vtable 0x71023fa168
class Unk_71023fa168 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;
};

class HangedLamp : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HangedLamp, ksys::act::ai::Ai)
public:
    explicit HangedLamp(const InitArg& arg);
    ~HangedLamp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    Unk_71023fa168 _38;
    // static_param at offset 0x60
    const bool* mDisableImpulseByArrow_s{};
};

}  // namespace uking::ai
