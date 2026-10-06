#pragma once

#include "Game/AI/aiUnkMessagePayloads.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"

// vtable 0x7102387728 (ForkGanonBeastHeadBarrier::_48): sends message 0x80000a9 (BaseProcLink + position payload,
// see Unk_7102450a68). Its functions are in the ForkGanonBeastHeadBarrier TU (0x7100143a20..).
class Unk_7102387728 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProc* proc, const sead::Vector3f& pos) {
        sead::ScopedLock<sead::JobQueueLock> lock(&_18.mLock);
        _18._0.acquire(proc, false);
        _18._10 = pos;
    }

    Unk_7102450a68_Payload _18;
};

namespace uking::action {

class ForkGanonBeastHeadBarrier : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkGanonBeastHeadBarrier, ksys::act::ai::Action)
public:
    explicit ForkGanonBeastHeadBarrier(const InitArg& arg);
    ~ForkGanonBeastHeadBarrier() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool sub_7100154628();

    // static_param at offset 0x20
    const float* mBarrierRad_s{};
    // static_param at offset 0x28
    const float* mBarrierFront_s{};
    // static_param at offset 0x30
    const float* mBarrierBack_s{};
    // static_param at offset 0x38
    const float* mBarrierHeight_s{};
    // static_param at offset 0x40
    const float* mBarrierHeightMax_s{};
    Unk_7102387728 _48{mActor, 0x80000a9};
};
KSYS_CHECK_SIZE_NX150(ForkGanonBeastHeadBarrier, 0x80);

}  // namespace uking::action
