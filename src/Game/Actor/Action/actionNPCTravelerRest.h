#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCTravelerRest : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCTravelerRest, ksys::act::ai::Action)
public:
    explicit NPCTravelerRest(const InitArg& arg);
    ~NPCTravelerRest() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    bool* mIsWarpHorse_d{};
    u16 _28 = 0;
    u8 _2a[0x60 - 0x2a];
};

}  // namespace uking::action
