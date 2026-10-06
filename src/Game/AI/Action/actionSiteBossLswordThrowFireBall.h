#pragma once

#include <container/seadSafeArray.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::action {

class SiteBossLswordThrowFireBall : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossLswordThrowFireBall, ksys::act::ai::Action)
public:
    explicit SiteBossLswordThrowFireBall(const InitArg& arg);
    ~SiteBossLswordThrowFireBall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x710025f148 (declared only): resets entry `idx`, copies the bind node name and sends 0x58 to `link`.
    void sub_710025F148(ksys::act::BaseProcLink* link, s32 idx);
    // 0x710025f368 (declared only): out of line in the original.
    void sub_710025F368();
    // 0x710025f958 (declared only): sets up entry `idx` and sends 0x3a to `link`.
    void sub_710025F958(ksys::act::BaseProcLink* link, const sead::Vector3f& pos, s32 idx, f32 scale);
    void calc_() override;

    // static_param at offset 0x20
    const float* mInitVelocity_s{};
    // static_param at offset 0x28
    const float* mFireBallAng_s{};
    // static_param at offset 0x30
    const bool* mIsThrowAll_s{};
    // static_param at offset 0x38
    sead::SafeString mThrowASName_s{};
    // static_param at offset 0x48
    sead::SafeString mBindNodeName_s{};
    // dynamic_param at offset 0x58
    bool* mIsThrowChildDevice_d{};
    // dynamic_param at offset 0x60
    sead::SafeString mPartsName_d{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x78
    ksys::act::BaseProcLink* mTargetActor_d{};
    bool _80 = false;
    u8 _81[0x7];
    struct Entry {
        sead::Vector3f _0;
        sead::Vector3f _c;
        ksys::act::BaseProcLink _18;
        f32 _28 = 0;
        sead::FixedSafeString<32> _30;
    };
    // 0x25ee64 is the out-of-line destructor of this array type (called by D1 / D0).
    sead::SafeArray<Entry, 21> _88;
    u8 _910[0x18];
};
KSYS_CHECK_SIZE_NX150(SiteBossLswordThrowFireBall, 0x928);

}  // namespace uking::action
