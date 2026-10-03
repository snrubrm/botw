#pragma once

#include "Game/AI/aiUnkDamageCallbacks.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class InvincibleHiddenOctarock : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(InvincibleHiddenOctarock, ksys::act::ai::Ai)
public:
    explicit InvincibleHiddenOctarock(const InitArg& arg);
    ~InvincibleHiddenOctarock() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    Unk_71024519a8 _38;
};

}  // namespace uking::ai
