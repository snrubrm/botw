#pragma once

#include <container/seadBuffer.h>
#include "Game/AI/aiActorLink.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class LimitedTimeredActorCreator : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LimitedTimeredActorCreator, ksys::act::ai::Ai)
public:
    explicit LimitedTimeredActorCreator(const InitArg& arg);
    ~LimitedTimeredActorCreator() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void createOneActor();
    void sub_7100482EB0();

protected:
    // static_param at offset 0x38
    const float* mCreateTimer_s{};
    // static_param at offset 0x40
    const float* mCreateTimerRand_s{};
    // static_param at offset 0x48
    sead::SafeString mCreateActorName_s{};
    // map_unit_param at offset 0x58
    const int* mCreateLimit_m{};
    // map_unit_param at offset 0x60
    sead::SafeString mActorName_m{};
    // aitree_variable at offset 0x70
    void* mGeneratedActorLink_a{};
    ksys::act::Unk_7100d3bc4c _78{mActor, 1.0f};
    ksys::act::BaseProcHandle _90;
    sead::Buffer<Unk_7102370e70> _a0;
};

}  // namespace uking::ai
