#pragma once

#include "Game/AI/AI/aiWeaponRootAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ASWeaponRoot : public WeaponRootAI {
    SEAD_RTTI_OVERRIDE(ASWeaponRoot, WeaponRootAI)
public:
    explicit ASWeaponRoot(const InitArg& arg);
    ~ASWeaponRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m36() override;
    void m37() override;
    void m38() override;
    void m39() override;
    void m40() override;

    void sub_7100323494();

protected:
    // static_param at offset 0xe8
    sead::SafeString mEquiped_s{};
    // static_param at offset 0xf8
    sead::SafeString mUnEquiped_s{};
    // static_param at offset 0x108
    sead::SafeString mThrown_s{};
    // static_param at offset 0x118
    sead::SafeString mStick_s{};
    // static_param at offset 0x128
    sead::SafeString mCancelStick_s{};
};

}  // namespace uking::ai
