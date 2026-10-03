#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class PriestBossEyeBeam : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PriestBossEyeBeam, ksys::act::ai::Ai)
public:
    explicit PriestBossEyeBeam(const InitArg& arg);
    ~PriestBossEyeBeam() override;

    bool isChangeable() const override { return *mParams.mIsChangeable_s; }
    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34();
    virtual bool m35();
    virtual void m36(sead::Vector3f* pos);
    virtual void m37(sead::Vector3f* pos) { *pos = _ac; }
    virtual void m38(const sead::Vector3f& pos);
    virtual bool m39(const sead::Vector3f& start, const sead::Vector3f& end);
    virtual void m40(const sead::Matrix34f& mtx, const sead::Vector3f& pos, f32 x, f32 y);
    virtual void m41();
    virtual void m42(const sead::Vector3f& pos);
    virtual void m43() { changeChild("チャージ"); }
    virtual void m44(const sead::Vector3f& pos);
    virtual void m45() { changeChild("待機"); }
    virtual sead::SafeString m46() { return "Beam"; }

    void sub_710051459C();

protected:
    struct Params {
        // static_param at offset 0x38
        const int* mAtMinDamage_s{};
        // static_param at offset 0x40
        const int* mAttackPower_s{};
        // static_param at offset 0x48
        const int* mAttackPowerForPlayer_s{};
        // static_param at offset 0x50
        const int* mShotReviseAngleXU_s{};
        // static_param at offset 0x58
        const int* mShotReviseAngleXD_s{};
        // static_param at offset 0x60
        const int* mShotReviseAngleY_s{};
        // static_param at offset 0x68
        const bool* mIsCreateGuardEffect_s{};
        // static_param at offset 0x70
        const bool* mIsChangeable_s{};
        // static_param at offset 0x78
        const sead::Vector3f* mReflectOffset_s{};
        // static_param at offset 0x80
        const sead::Vector3f* mShotOffset_s{};
    };
    Params mParams;
    ksys::act::BaseProcLink _88;
    sead::SafeString _98;
    bool _a8 = true;
    sead::Vector3f _ac = sead::Vector3f::zero;
};
KSYS_CHECK_SIZE_NX150(PriestBossEyeBeam, 0xb8);

}  // namespace uking::ai
