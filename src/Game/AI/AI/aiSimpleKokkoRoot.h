#pragma once

#include "Game/AI/aiActorLink.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class SimpleKokkoRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SimpleKokkoRoot, ksys::act::ai::Ai)
public:
    explicit SimpleKokkoRoot(const InitArg& arg);
    ~SimpleKokkoRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mAliveTime_s{};
    // aitree_variable at offset 0x40
    Unk_7102370e70** mAttackTargetActorLink_a{};
    Unk_7102370e70 _48;
    ksys::Timer _60{};
    f32 _6c = 0;
};
KSYS_CHECK_SIZE_NX150(SimpleKokkoRoot, 0x70);

}  // namespace uking::ai
