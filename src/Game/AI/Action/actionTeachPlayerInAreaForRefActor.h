#pragma once

#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"

namespace uking::action {

class TeachPlayerInAreaForRefActor : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(TeachPlayerInAreaForRefActor, ksys::act::ai::Action)
public:
    explicit TeachPlayerInAreaForRefActor(const InitArg& arg);
    ~TeachPlayerInAreaForRefActor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // 0x710029450c (placeholder name; out of line in the original).
    void sub_710029450C();

    // static_param at offset 0x20
    const float* mNextTimer_s{};
    bool _28 = false;
    ksys::act::Unk_7100d3bce4 _30{mActor};
    Unk_71023c5480 _48{mActor, 0x80000b8};
};

}  // namespace uking::action
