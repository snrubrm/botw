#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/VFRValue.h"

namespace ksys::phys {
class RigidBody;
}

namespace uking::ai {

// Payload of the messages 0x800003a / 0x8000058 sent to SiteBoss projectiles (0x68 bytes; an array of
// them lives in the unnamed sender class whose send function is at 0x710025f148, which fills
// `_c`, `_18`, `_28` and the node name). Name and members are guesses from the readers.
struct SiteBossProjectilePayload {
    sead::Vector3f _0;
    sead::Vector3f _c;
    ksys::act::BaseProcLink _18;
    f32 _28;
    sead::FixedSafeString<32> mNodeName;
};
static_assert(sizeof(SiteBossProjectilePayload) == 0x68);

class SiteBossChemicalProjectile : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossChemicalProjectile, ksys::act::ai::Ai)
public:
    explicit SiteBossChemicalProjectile(const InitArg& arg);
    ~SiteBossChemicalProjectile() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    bool handleMessage_(const ksys::Message* message) override;
    void loadParams_() override;

    virtual const sead::SafeString& m34();
    virtual sead::Vector3f m35();
    virtual sead::Vector3f m36();
    virtual void m37();
    virtual void m38();
    virtual bool m39();
    virtual bool m40();
    virtual bool m41();
    virtual void m42();
    virtual void m43(bool a);
    virtual void m44();
    virtual const sead::Vector3f& m45();
    virtual void m46(const sead::Vector3f& v);
    virtual void m47(f32 v);
    virtual const sead::Vector3f& m48();
    virtual void m49(const sead::Vector3f& v);
    virtual u32 m50();
    virtual u32 m51();
    virtual void m52(ksys::phys::RigidBody* body);
    virtual void m53(ksys::phys::RigidBody* body);
    virtual bool m54();
    virtual bool m55();
    virtual bool m56();
    virtual f32 m57();

    // 0x71003eb688: changes to the explosion child, passing IsPlayerAttack (m55), AttackPower and
    // AtMinDamage; the first call goes to the reflected explosion state. Placeholder name.
    void sub_71003EB688();

protected:
    // static_param at offset 0x38
    const float* mExplosionTime_s{};
    // static_param at offset 0x40
    const float* mChaseAngleLimit_s{};
    // static_param at offset 0x48
    const float* mReflectSpeedRate_s{};
    // static_param at offset 0x50
    const bool* mIsForceDelete_s{};
    // static_param at offset 0x58
    const bool* mIsAdjustHeight_s{};
    // static_param at offset 0x60
    const bool* mIsSetParentSystemGroupHandler_s{};
    // static_param at offset 0x68
    const bool* mIsSetBindSpeed_s{};
    // static_param at offset 0x70
    const bool* mIsIgnoreObject_s{};
    // static_param at offset 0x78
    sead::SafeString mBindNodeName_s{};
    // map_unit_param at offset 0x88
    const int* mAttackPower_m{};
    // map_unit_param at offset 0x90
    const int* mAtMinDamage_m{};
    // map_unit_param at offset 0x98
    const float* mScaleTime_m{};
    // map_unit_param at offset 0xa0
    const float* mRange_m{};
    // map_unit_param at offset 0xa8
    const float* mAtkRadiusMax_m{};
    sead::Vector3f _b0 = sead::Vector3f::zero;
    sead::Vector3f _bc = sead::Vector3f::zero;
    sead::Vector3f _c8;
    bool _d4 = false;
    bool _d5 = false;
    bool _d6 = false;
    bool _d7 = false;
    bool _d8 = false;
    bool _d9 = false;
    f32 _dc = 0.1f;
    ksys::VFRValue _e0;
    u32 _ec;
    sead::Vector3f _f0;
    u8 _fc[0x108 - 0xfc];
    ksys::act::BaseProcLink _108;
    f32 _118 = 0;
    sead::FixedSafeString<32> _120;
    ksys::act::BaseProcLink _158;
    ksys::act::BaseProcLink _168;
    void* _178 = nullptr;
};
KSYS_CHECK_SIZE_NX150(SiteBossChemicalProjectile, 0x180);

}  // namespace uking::ai
