#pragma once

#include "Game/AI/Action/actionHornUseBase.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/Awareness/actAITerror.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HornUse : public HornUseBase {
    SEAD_RTTI_OVERRIDE(HornUse, HornUseBase)
public:
    explicit HornUse(const InitArg& arg);
    ~HornUse() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x78
    const int* mSpreadTime_s{};
    // static_param at offset 0x80
    const int* mTerrorLevel_s{};
    // static_param at offset 0x88
    const float* mSpreadDist_s{};
    // static_param at offset 0x90
    const int* mNoticeMaskState_s{};
    /* 0x098 */ Unk_710235abc8 _98{mActor, 0x8000006};
    /* 0x0f0 */ ksys::act::AITerror _f0{mActor};
    /* 0x1a8 */ f32 _1a8 = 0;
};
KSYS_CHECK_SIZE_NX150(HornUse, 0x1b0);

}  // namespace uking::action
