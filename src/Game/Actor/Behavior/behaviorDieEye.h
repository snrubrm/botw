#pragma once

#include <prim/seadSafeString.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class DieEye : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(DieEye, ksys::act::ai::Behavior)
public:
    explicit DieEye(const InitArg& arg);
    ~DieEye() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ sead::SafeString mLeftEyeLidName_s{};
    /* 0x38 */ sead::SafeString mRightEyeLidName_s{};
    /* 0x48 */ const sead::Vector3f* mCloseOffset_s{};
};
KSYS_CHECK_SIZE_NX150(DieEye, 0x50);

}  // namespace uking::behavior
