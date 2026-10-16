#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class InvalidateCondition : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(InvalidateCondition, ksys::act::ai::Behavior)
public:
    explicit InvalidateCondition(const InitArg& arg);
    ~InvalidateCondition() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ const bool* mInvalidBurn_s{};
    /* 0x30 */ const bool* mInvalidIce_s{};
    /* 0x38 */ const bool* mInvalidElectric_s{};
};
KSYS_CHECK_SIZE_NX150(InvalidateCondition, 0x40);

}  // namespace uking::behavior
