#pragma once

#include "Game/AI/aiUnk_71025b1808.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyFortressMgrTag : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyFortressMgrTag, ksys::act::ai::Ai)
public:
    explicit EnemyFortressMgrTag(const InitArg& arg);
    ~EnemyFortressMgrTag() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;
    bool handleAck_(const ksys::MessageAck& ack) override;

protected:
    // static_param at offset 0x38
    const int* mCheckInterval_s{};
    // static_param at offset 0x40
    const float* mChangePer_s{};
    // aitree_variable at offset 0x48 (points to _50)
    Unk_71025afb58** mRegistedActorUnit_a{};
    Unk_71025b1808 _50;
    f32 _438 = 0;
    s32 _43c = 0;
    s32 _440 = 0;
    bool _444 = false;
    s32 _448 = -1;
};
KSYS_CHECK_SIZE_NX150(EnemyFortressMgrTag, 0x450);

}  // namespace uking::ai
