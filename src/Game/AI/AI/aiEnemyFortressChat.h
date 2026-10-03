#pragma once

#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyFortressChat : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyFortressChat, ksys::act::ai::Ai)
public:
    explicit EnemyFortressChat(const InitArg& arg);
    ~EnemyFortressChat() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void sub_710038E110();
protected:
    // static_param at offset 0x38
    const float* mNextPer_s{};
    // aitree_variable at offset 0x40
    void* mRegistedActorUnit_a{};
    ksys::act::BaseProcLink _48;
    Unk_71023e78b0 _58{mActor, 0x80000a1};
};

}  // namespace uking::ai
