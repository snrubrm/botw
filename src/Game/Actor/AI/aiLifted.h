#pragma once

#include "Game/Actor/aiUnk_7102357210.h"
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
    bool handleMessage_(const ksys::Message* message) override;

protected:
    // 0x7100482000 (placeholder name): changes to 投擲 with the throw power and direction of `velocity`.
    void sub_7100482000(const sead::Vector3f& velocity, bool is_shot_by_player);

    // static_param at offset 0x38
    const bool* mIsGetItem_s{};
    u32 _40{};
    bool _44{};
    Unk_71023da100 _48;
};

}  // namespace uking::ai
