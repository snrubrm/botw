#pragma once

#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GrudgeEyeball;

// vtable 0x71023f64e0
class Unk_71023f64e0 : public dmg::DamageCallback {
public:
    explicit Unk_71023f64e0(GrudgeEyeball* owner) : _28(owner) {}
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    GrudgeEyeball* _28;
};

class GrudgeEyeball : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GrudgeEyeball, ksys::act::ai::Ai)
public:
    explicit GrudgeEyeball(const InitArg& arg);
    ~GrudgeEyeball() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const int* mEyeballFirstState_m{};
    Unk_71023f64e0 _40{this};
    bool _70 = false;
};

}  // namespace uking::ai
