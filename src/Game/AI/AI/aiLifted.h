#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class Lifted : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(Lifted, ksys::act::ai::Ai)
public:
    explicit Lifted(const InitArg& arg);
    ~Lifted() override = default;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsGetItem_s{};
    u32 _40{};
    bool _44{};
    Unk_71023da100 _48;
};

}  // namespace uking::ai
