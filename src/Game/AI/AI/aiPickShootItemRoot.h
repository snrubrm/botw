#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class PickShootItemRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PickShootItemRoot, ksys::act::ai::Ai)
public:
    explicit PickShootItemRoot(const InitArg& arg);
    ~PickShootItemRoot() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mRemainTime_s{};
    ksys::Timer _40;
};
KSYS_CHECK_SIZE_NX150(PickShootItemRoot, 0x50);

}  // namespace uking::ai
