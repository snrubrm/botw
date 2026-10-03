#pragma once

#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_71000b0800.h"
#include "Game/AI/aiUnk_71025afb58.h"
#include "Game/AI/aiUnk_71025be918.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class GiantWeaponGrabAS : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(GiantWeaponGrabAS, ksys::act::ai::Behavior)
public:
    explicit GiantWeaponGrabAS(const InitArg& arg);
    ~GiantWeaponGrabAS() override;
    void m8() override;
    void loadParams() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m9() override;

    // 0x7100626590 / 0x7100626768 (lane4 s23): the weapon frame (`frame`) is set on the AS slots of both hands.
    void sub_7100626590(f32 frame, bool use_b);
    void sub_7100626768();

    /* 0x28 */ const int* mTargetBone_s{};
    /* 0x30 */ const int* mWeaponIdx_s{};
    /* 0x38 */ const int* mLeftTargetBone_s{};
    /* 0x40 */ const float* mVeryThinFrame_s{};
    /* 0x48 */ const float* mThinFrame_s{};
    /* 0x50 */ const float* mNormalFrame_s{};
    /* 0x58 */ const float* mThickFrame_s{};
    /* 0x60 */ sead::SafeString mASName_s{};
    /* 0x70 */ sead::SafeString mPartialBone0_s{};
    /* 0x80 */ sead::SafeString mPartialBone1_s{};
    /* 0x90 */ sead::SafeString mPartialBone2_s{};
    /* 0xa0 */ sead::SafeString mLeftPartialBone0_s{};
    /* 0xb0 */ sead::SafeString mLeftPartialBone1_s{};
    /* 0xc0 */ sead::SafeString mLeftPartialBone2_s{};
    /* 0xd0 */ void* mGiantPartBoneUnit_a{};
    /* 0xd8 */ bool _d8 = false;
    /* 0xd9 */ bool _d9 = false;
    /* 0xe0 */ Unk_71000b0800<Unk_71025be918> _e0;
};
KSYS_CHECK_SIZE_NX150(GiantWeaponGrabAS, 0xe8);

}  // namespace uking::behavior
