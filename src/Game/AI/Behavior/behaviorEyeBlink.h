#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class EyeBlink : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(EyeBlink, ksys::act::ai::Behavior)
public:
    explicit EyeBlink(const InitArg& arg);
    void loadParams() override;
    bool m6(sead::Heap* heap) override;  // not decompiled yet (0x71006222d4)
    void m7() override;  // not decompiled yet (0x7100622444)
    void m8() override;  // not decompiled yet (0x71006223b4)
    void m9() override;  // not decompiled yet (0x710062252c)
    ~EyeBlink() override;  // not decompiled yet

    /* 0x28 */ const int* mTimerMin_s{};
    /* 0x30 */ const int* mTimerMax_s{};
    /* 0x38 */ const int* mBlinkCount_s{};
    /* 0x40 */ sead::SafeString mLeftEyeLidName_s{};
    /* 0x50 */ sead::SafeString mRightEyeLidName_s{};
    /* 0x60 */ const sead::Vector3f* mCloseOffset_s{};
    /* 0x68 */ u32 _68 = 0;
};
KSYS_CHECK_SIZE_NX150(EyeBlink, 0x70);

}  // namespace uking::behavior
