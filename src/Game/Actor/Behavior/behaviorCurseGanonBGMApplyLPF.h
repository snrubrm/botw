#pragma once

#include "Game/Actor/aiUnk_7100FFDFDC.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class CurseGanonBGMApplyLPF : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(CurseGanonBGMApplyLPF, ksys::act::ai::Behavior)
public:
    explicit CurseGanonBGMApplyLPF(const InitArg& arg);
    ~CurseGanonBGMApplyLPF() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ const float* mLPF_s{};
    /* 0x30 */ Unk_7100ffe5ec* _30 = nullptr;
};
KSYS_CHECK_SIZE_NX150(CurseGanonBGMApplyLPF, 0x38);

}  // namespace uking::behavior
