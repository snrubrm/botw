#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SandwormNavSearchWait : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SandwormNavSearchWait, ksys::act::ai::Ai)
public:
    explicit SandwormNavSearchWait(const InitArg& arg);
    ~SandwormNavSearchWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x710055b34c: changes to the "移動" child, aiming at the sandworm anchor position when this actor is above it and more than 1 away (XZ)
    void sub_710055B34C();
    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
