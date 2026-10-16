#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetWindForceScale : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetWindForceScale, ksys::act::ai::Behavior)
public:
    explicit SetWindForceScale(const InitArg& arg);
    ~SetWindForceScale() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ const float* mWindScale_s{};
};
KSYS_CHECK_SIZE_NX150(SetWindForceScale, 0x30);

}  // namespace uking::behavior
