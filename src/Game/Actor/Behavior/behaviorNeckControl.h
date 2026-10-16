#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class NeckControl : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(NeckControl, ksys::act::ai::Behavior)
public:
    explicit NeckControl(const InitArg& arg);
    ~NeckControl() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    virtual bool m14() { return false; }
    virtual void m15(sead::Vector3f* out) {}

    /* 0x28 */ const float* mOffsetToTargetDirXZ_s{};
    /* 0x30 */ const bool* mIsUpdatePos_s{};
};

}  // namespace uking::behavior
