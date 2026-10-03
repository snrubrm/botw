#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class WithoutWeaponArrow : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WithoutWeaponArrow, ksys::act::ai::Ai)
public:
    explicit WithoutWeaponArrow(const InitArg& arg);
    ~WithoutWeaponArrow() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    virtual void m34(const sead::Vector3f& a1, bool a2, const char* child_name);
    virtual void m35();
    virtual void m36();
    virtual bool m37(bool* broke_ice_block, bool* hit_player);
    virtual bool m38();
    virtual bool m39();
    virtual void m40();
    virtual s32 m41();
    // m42..m46 are inline: their only copies are in the SiteBossGaleArrowRoot and
    // ChildDeviceReflectArrow TUs.
    virtual f32 m42() { return *mAccel_s; }
    virtual f32 m43() { return *mAimSpeed_s; }
    virtual s32 m44() { return *mAttackPower_m; }
    virtual s32 m45() { return *mAtMinDamage_m; }
    virtual bool m46() { return _115; }
    virtual s32 m47();
    virtual bool m48();

protected:
    // static_param at offset 0x38
    const int* mAtAttr_s{};
    // static_param at offset 0x40
    const int* mStickTime_s{};
    // static_param at offset 0x48
    const float* mAccel_s{};
    // static_param at offset 0x50
    const float* mAimSpeed_s{};
    // static_param at offset 0x58
    const float* mFallAccel_s{};
    // static_param at offset 0x60
    const float* mFallAimSpeed_s{};
    // static_param at offset 0x68
    const float* mGravity_s{};
    // static_param at offset 0x70
    const float* mAtRange_s{};
    // static_param at offset 0x78
    const float* mAtImpulse_s{};
    // static_param at offset 0x80
    const float* mAtImpact_s{};
    // static_param at offset 0x88
    const float* mReflectDamageRate_s{};
    // static_param at offset 0x90
    const bool* mCanReflect_s{};
    // static_param at offset 0x98
    const bool* mIsReflectToParent_s{};
    // static_param at offset 0xa0
    const bool* mIsDelete_s{};
    // static_param at offset 0xa8
    const bool* mIsBreakIceBlock_s{};
    // static_param at offset 0xb0
    const bool* mIsAtHitPlayerIgnore_s{};
    // static_param at offset 0xb8
    const bool* mIsDeleteAtHit_s{};
    // static_param at offset 0xc0
    sead::SafeString mBindNodeName_s{};
    // static_param at offset 0xd0
    sead::SafeString mCallHitSEKey_s{};
    // static_param at offset 0xe0
    const sead::Vector3f* mReflectOffset_s{};
    // static_param at offset 0xe8
    const sead::Vector3f* mRotOffset_s{};
    // static_param at offset 0xf0
    const sead::Vector3f* mTransOffset_s{};
    // map_unit_param at offset 0xf8
    const int* mAtMinDamage_m{};
    // map_unit_param at offset 0x100
    const int* mAttackPower_m{};
    ksys::Timer _108{};
    bool _114 = true;
    bool _115 = false;
    bool _116 = false;
    sead::Vector3f _118;
    sead::Vector3f _124;
    u8 _130[0x13c - 0x130];
    s32 _13c = 1;
};
KSYS_CHECK_SIZE_NX150(WithoutWeaponArrow, 0x140);

}  // namespace uking::ai
