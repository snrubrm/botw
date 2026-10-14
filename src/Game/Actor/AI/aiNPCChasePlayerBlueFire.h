#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"

namespace uking::ai {

class NPCChasePlayerBlueFire : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCChasePlayerBlueFire, ksys::act::ai::Ai)
public:
    explicit NPCChasePlayerBlueFire(const InitArg& arg);
    ~NPCChasePlayerBlueFire() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void sub_71004C34AC();
    void sub_71004C35CC();
    void sub_71004C370C();

protected:
    // static_param at offset 0x38
    const int* mLostTimer_s{};
    // static_param at offset 0x40
    const float* mNearDist_s{};
    // static_param at offset 0x48
    const float* mLeaveDist_s{};
    // static_param at offset 0x50
    const float* mLostDist_s{};
    ksys::act::Unk_7100d3bce4 _58{mActor};
};
KSYS_CHECK_SIZE_NX150(NPCChasePlayerBlueFire, 0x70);

}  // namespace uking::ai
