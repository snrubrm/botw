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
    // 0x71003f73d8 (placeholder name): paths to the closest nav mesh point of the target position.
    void sub_71003F73D8();
protected:
    ksys::Timer _38;
};

}  // namespace uking::ai
