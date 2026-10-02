#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetWindForceScale : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetWindForceScale, ksys::act::ai::Behavior)
public:
    explicit SetWindForceScale(const InitArg& arg);
    ~SetWindForceScale() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const float* mWindScale_s{};
};
KSYS_CHECK_SIZE_NX150(SetWindForceScale, 0x30);

}  // namespace uking::behavior
