#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace ksys::act {
class Unk_7100d860d8;
}

namespace uking::behavior {

class NeckParamChange : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(NeckParamChange, ksys::act::ai::Behavior)
public:
    explicit NeckParamChange(const InitArg& arg);
    ~NeckParamChange() override;
    bool m6(sead::Heap* heap) override;
    void loadParams() override;
    void m7() override;
    void m8() override;
    void m9() override;

    /* 0x28 */ const float* mULimit_s{};
    /* 0x30 */ const float* mDLimit_s{};
    /* 0x38 */ const float* mLLimit_s{};
    /* 0x40 */ const float* mRLimit_s{};
    /* 0x48 */ const float* mRotRatio_s{};
    /* 0x50 */ const float* mRetRotRatio_s{};
    /* 0x58 */ const float* mMinRotate_s{};
    /* 0x60 */ const float* mMaxRotate_s{};
    /* 0x68 */ const float* mOffsetLR_s{};
    /* 0x70 */ const float* mOffsetUD_s{};
    // The spine controller's limits before this behavior changed them (saved by m8, restored by m9).
    // Placeholder name; the two methods are out-of-line in the original (0x710062cb24 / 0x710062cd74).
    struct Saved {
        void sub_710062CB24(ksys::act::Unk_7100d860d8* unit);  // save
        void sub_710062CD74(ksys::act::Unk_7100d860d8* unit);  // restore

        /* 0x00 */ f32 _0 = 0;  // |U|
        /* 0x04 */ f32 _4 = 0;  // |D|
        /* 0x08 */ f32 _8 = 0;  // |L|
        /* 0x0c */ f32 _c = 0;  // |R|
        /* 0x10 */ f32 _10 = 0;
        /* 0x14 */ f32 _14 = 0;
        /* 0x18 */ u32 _18 = 0;
        /* 0x1c */ f32 _1c = 0;
        /* 0x20 */ f32 _20 = 0;
    };
    /* 0x78 */ Saved _78;
};
KSYS_CHECK_SIZE_NX150(NeckParamChange, 0xa0);

}  // namespace uking::behavior
