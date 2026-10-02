#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class GiantEscapeFromDamageWater : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GiantEscapeFromDamageWater, ksys::act::ai::Ai)
public:
    explicit GiantEscapeFromDamageWater(const InitArg& arg);
    ~GiantEscapeFromDamageWater() override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void sub_71003F6CF0();
protected:
    ksys::Timer _38;
};

}  // namespace uking::ai
