#pragma once

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
    // 0x710025f368 (declared only): out of line in the original.
    void sub_710025F368();
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
        ksys::act::BaseProcLink _0;
        s32 _10 = 0;
        sead::FixedSafeString<32> _18;
        u8 _50[0x18];
    };
    // Placeholder name (0x25ee64 is its out-of-line destructor, called by D1 / D0): a 0x18-byte header and the 21
    // entries.
    struct Entries {
        ~Entries();
        u8 _0[0x18];
        Entry _18[21];
    };
    Entries _88;
};
KSYS_CHECK_SIZE_NX150(SiteBossLswordThrowFireBall, 0x928);

}  // namespace uking::action
