#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelRodeo : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelRodeo, ksys::act::ai::Ai)
public:
    explicit LynelRodeo(const InitArg& arg);
    ~LynelRodeo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    void sub_7100499D48();
    void sub_7100499E08();

    // aitree_variable at offset 0x38
    int* mLynelRodeoAttackHitNum_a{};
};

}  // namespace uking::ai
