#pragma once

#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AirOctaBurnReaction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AirOctaBurnReaction, ksys::act::ai::Ai)
public:
    explicit AirOctaBurnReaction(const InitArg& arg);
    ~AirOctaBurnReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x71002faa64 (placeholder name)
    bool sub_71002FAA64();

    // static_param at offset 0x38
    const float* mDisconnectTime_s{};
    // static_param at offset 0x40
    const float* mDisconnectRandTime_s{};
    // static_param at offset 0x48
    const float* mSingleBurnTime_s{};
    // static_param at offset 0x50
    const float* mChangeRandTime_s{};
    // aitree_variable at offset 0x58
    Unk_71025afb58** mAirOctaDataMgr_a{};
    u32 _60{};  // state: 0 / 1 (disconnected) / 2
    f32 _64{};
    f32 _68{};
    f32 _6c{};
};

}  // namespace uking::ai
