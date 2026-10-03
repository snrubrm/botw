#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"

// Damage callback (vtable 0x71023f8530) without RTTI of its own; its functions are in the
// GuardianMiniChangeWeapon translation unit. Placeholder name.
class Unk_71023f8530 : public uking::dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override {
        if (*a5 != -1)
            *a5 = 1;
    }
};

namespace uking::ai {

class GuardianMiniChangeWeapon : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardianMiniChangeWeapon, ksys::act::ai::Ai)
public:
    explicit GuardianMiniChangeWeapon(const InitArg& arg);
    ~GuardianMiniChangeWeapon() override;
    bool isFinished() const override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    void sub_710041AAD4();

protected:
    // static_param at offset 0x38
    const int* mRotValue_s{};
    // static_param at offset 0x40
    const float* mRotSpeed_s{};
    // static_param at offset 0x48
    sead::SafeString mRootNodeName_s{};
    // static_param at offset 0x58
    sead::SafeString mDamageNodeName_s{};
    // static_param at offset 0x68
    sead::SafeString mDamageASName_s{};
    Unk_71023f8530 _78;
    Unk_71023f83e8* _a0{};
    Unk_7102450498 _a8;
};
KSYS_CHECK_SIZE_NX150(GuardianMiniChangeWeapon, 0xf8);

}  // namespace uking::ai
