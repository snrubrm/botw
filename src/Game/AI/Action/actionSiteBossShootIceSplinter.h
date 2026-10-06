#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::action {

class SiteBossShootIceSplinter : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossShootIceSplinter, ksys::act::ai::Action)
public:
    explicit SiteBossShootIceSplinter(const InitArg& arg);
    ~SiteBossShootIceSplinter() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isFinished() const override;

protected:
    // 0x710026354c (declared only): out of line in the original.
    void sub_710026354C(int idx);
    void calc_() override;

    // static_param at offset 0x20
    const int* mThrowIdxOffset_s{};
    // static_param at offset 0x28
    const float* mInitVelocity_s{};
    // static_param at offset 0x30
    sead::SafeString mThrowASName_s{};
    // static_param at offset 0x40
    sead::SafeString mBindNodeName_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x58
    ksys::act::BaseProcLink* mTargetActor_d{};
    bool _60 = false;
    bool _61 = false;
    bool _62 = false;
    s32 _64 = 0;
    struct Entry {
        ksys::act::BaseProcLink _0;
        s32 _10 = 0;
        sead::FixedSafeString<32> _18;
        u8 _50[0x18];
    };
    // Placeholder name (0x2631cc is its out-of-line ctor): a 0x18-byte header, one entry and an array of 8 entries.
    struct Entries {
        Entries();
        u8 _0[0x18];
        Entry _18;
        Entry _80[8];
    };
    Entries _68;
};

}  // namespace uking::action
