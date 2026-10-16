#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class IgnoreGiantArmorCondition : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(IgnoreGiantArmorCondition, ksys::act::ai::Behavior)
public:
    explicit IgnoreGiantArmorCondition(const InitArg& arg);
    ~IgnoreGiantArmorCondition() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ bool* mIgnoreGiantArmorCondition_a{};
};
KSYS_CHECK_SIZE_NX150(IgnoreGiantArmorCondition, 0x30);

}  // namespace uking::behavior
