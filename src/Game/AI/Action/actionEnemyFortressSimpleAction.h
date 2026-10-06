#pragma once

#include "Game/AI/Action/actionForkTimer.h"
#include "Game/AI/aiUnkMessagePayloads.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"

// vtable 0x7102379de0 (EnemyFortressSimpleAction::_48): sends message 0x80000a5 (BaseProcLink payload,
// see Unk_7102450708). Its functions are in the EnemyFortressSimpleAction TU (0x7100109ddc..).
class Unk_7102379de0 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProc* proc) {
        sead::ScopedLock<sead::JobQueueLock> lock(&_18.mLock);
        _18.mLink.acquire(proc, false);
        _18._10 = 0;
    }

    Unk_7102379de0_Payload _18;
};

// vtable 0x7102379e38 (EnemyFortressSimpleAction::_78): sends message 0x80000a6 (no payload).
class Unk_7102379e38 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

namespace uking::action {

class EnemyFortressSimpleAction : public ForkTimer {
    SEAD_RTTI_OVERRIDE(EnemyFortressSimpleAction, ForkTimer)
public:
    explicit EnemyFortressSimpleAction(const InitArg& arg);
    ~EnemyFortressSimpleAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    Unk_7102379de0 _48{mActor, 0x80000a5};
    Unk_7102379e38 _78{mActor, 0x80000a6};
    // static_param at offset 0x90
    const int* mNoRequestTime_s{};
    // aitree_variable at offset 0x98
    void* mRegistedActorUnit_a{};
};
KSYS_CHECK_SIZE_NX150(EnemyFortressSimpleAction, 0xa0);

}  // namespace uking::action
