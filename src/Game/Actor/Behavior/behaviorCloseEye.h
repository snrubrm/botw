#pragma once

#include <prim/seadSafeString.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class CloseEye : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(CloseEye, ksys::act::ai::Behavior)
public:
    explicit CloseEye(const InitArg& arg);
    ~CloseEye() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ sead::SafeString mLeftEyeLidName_s{};
    /* 0x38 */ sead::SafeString mRightEyeLidName_s{};
    /* 0x48 */ const sead::Vector3f* mCloseOffset_s{};
};
KSYS_CHECK_SIZE_NX150(CloseEye, 0x50);

}  // namespace uking::behavior
