#pragma once

#include "Game/AI/Action/actionSwarmDamaged.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"

namespace uking::action {

class SwarmChemicalDamaged : public SwarmDamaged {
    SEAD_RTTI_OVERRIDE(SwarmChemicalDamaged, SwarmDamaged)
public:
    explicit SwarmChemicalDamaged(const InitArg& arg);
    ~SwarmChemicalDamaged() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x7100283004 (declared only): out of line in the original.
    void sub_7100283004(ksys::act::ai::InlineParamPack* params);
    // 0x71002831e4 (declared only): out of line in the original.
    void sub_71002831E4();
    void calc_() override;

    // static_param at offset 0x1c0
    const float* mResetChemicalTimer_s{};
    // static_param at offset 0x1c8
    const bool* mIsResetAllObject_s{};
    bool _1d0 = false;
    s32 _1d4 = -1;
    s32 _1d8 = -1;
    ksys::act::Unk_7100d3bce4 _1e0{mActor};
};

}  // namespace uking::action
