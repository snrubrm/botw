#pragma once

#include "Game/AI/Behavior/behaviorShowMessage3D.h"

namespace uking::behavior {

class ShowRandomMessage3D : public ShowMessage3D {
    SEAD_RTTI_OVERRIDE(ShowRandomMessage3D, ShowMessage3D)
public:
    explicit ShowRandomMessage3D(const InitArg& arg);
    ~ShowRandomMessage3D() override;
    void m7() override;
    void loadParams() override;
    void m14(sead::BufferedSafeString* out) override;  // not decompiled yet (0x7100640090)

    /* 0x128 */ const int* mRandomWidth_s{};
};
KSYS_CHECK_SIZE_NX150(ShowRandomMessage3D, 0x130);

}  // namespace uking::behavior
