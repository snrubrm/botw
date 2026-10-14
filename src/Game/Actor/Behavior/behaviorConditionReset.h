#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class ConditionReset : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(ConditionReset, ksys::act::ai::Behavior)
public:
    explicit ConditionReset(const InitArg& arg);
    ~ConditionReset() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void m11() override;

    /* 0x28 */ const bool* mIsResetBurn_s{};
    /* 0x30 */ const bool* mIsResetIce_s{};
    /* 0x38 */ const bool* mIsResetElectric_s{};
};
KSYS_CHECK_SIZE_NX150(ConditionReset, 0x40);

}  // namespace uking::behavior
