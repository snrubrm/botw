#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class IgnoreGiantArmorCondition : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(IgnoreGiantArmorCondition, ksys::act::ai::Behavior)
public:
    explicit IgnoreGiantArmorCondition(const InitArg& arg);
    ~IgnoreGiantArmorCondition() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ bool* mIgnoreGiantArmorCondition_a{};
};
KSYS_CHECK_SIZE_NX150(IgnoreGiantArmorCondition, 0x30);

}  // namespace uking::behavior
