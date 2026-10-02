#pragma once

#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

// vtable 0x7102424d70 (no RTTI of its own; D0 0x71005a90d8, call 0x71005a90ac): damage callback
// embedded twice in StalPartRoot. Cancels positive damage unless the damage type (*a4) is 3.
class Unk_7102424d70 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;
};

class StalPartRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StalPartRoot, ksys::act::ai::Ai)
public:
    explicit StalPartRoot(const InitArg& arg);
    ~StalPartRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    void sub_71005A8A8C(bool a1);

protected:
    Unk_7102424d70 _38;
    Unk_7102424d70 _60;
    // static_param at offset 0x88
    const float* mInvincibleTime_s{};
    s32 _90 = 0;
    ksys::Timer _94{0, 0};
    bool _a0 = false;
};
KSYS_CHECK_SIZE_NX150(StalPartRoot, 0xa8);

}  // namespace uking::ai
