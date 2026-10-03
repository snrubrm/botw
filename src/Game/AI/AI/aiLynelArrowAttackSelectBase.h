#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelArrowAttackSelectBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelArrowAttackSelectBase, ksys::act::ai::Ai)
public:
    explicit LynelArrowAttackSelectBase(const InitArg& arg);
    ~LynelArrowAttackSelectBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // 0x710048b294: sets flag 0x20 of the Lynel AI flags and changes to the "上空撃ち" child.
    void changeToShootUp(ksys::act::ai::InlineParamPack* params);
    // 0x710048b2b8: the target state (sub_71005D9744) is 2 or 3.
    bool sub_710048B2B8();

protected:
    // aitree_variable at offset 0x38
    int* mLynelAIFlags_a{};
};

}  // namespace uking::ai
