#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class PreyStun : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PreyStun, ksys::act::ai::Ai)
public:
    explicit PreyStun(const InitArg& arg);
    ~PreyStun() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mStunTime_s{};
    ksys::Timer _40;
};
KSYS_CHECK_SIZE_NX150(PreyStun, 0x50);

}  // namespace uking::ai
