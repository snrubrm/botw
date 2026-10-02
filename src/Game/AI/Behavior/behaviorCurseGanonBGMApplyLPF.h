#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class CurseGanonBGMApplyLPF : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(CurseGanonBGMApplyLPF, ksys::act::ai::Behavior)
public:
    explicit CurseGanonBGMApplyLPF(const InitArg& arg);
    ~CurseGanonBGMApplyLPF() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const float* mLPF_s{};
    /* 0x30 */ void* _30 = nullptr;
};
KSYS_CHECK_SIZE_NX150(CurseGanonBGMApplyLPF, 0x38);

}  // namespace uking::behavior
