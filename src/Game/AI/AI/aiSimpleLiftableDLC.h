#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SimpleLiftableDLC : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SimpleLiftableDLC, ksys::act::ai::Ai)
public:
    explicit SimpleLiftableDLC(const InitArg& arg);
    ~SimpleLiftableDLC() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    void sub_710056EA38();
    void sub_710056EC90();
    // Inline only (no out-of-line copy in the executable); placeholder name (as SimpleLiftable::x).
    void x();

protected:
    // static_param at offset 0x38
    const float* mScaleToLiftUp_s{};
    Unk_71024507c8 _40{0x1800004};
    Unk_71023da100 _80;
    bool _d0 = false;
    bool _d1 = false;
};
KSYS_CHECK_SIZE_NX150(SimpleLiftableDLC, 0xd8);

}  // namespace uking::ai
