#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class SiteBossSpearThrow : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossSpearThrow, ksys::act::ai::Ai)
public:
    explicit SiteBossSpearThrow(const InitArg& arg);
    ~SiteBossSpearThrow() override;

    bool isFailed() const override;
    bool isFinished() const override;
    bool isChangeable() const override { return true; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mAttackPower_s{};
    // static_param at offset 0x40
    const int* mAtMnDamage_s{};
    // static_param at offset 0x48
    const int* mAddAttackPower_s{};
    // static_param at offset 0x50
    sead::SafeString mThrowActorName_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    ksys::act::BaseProcHandle _68;
    ksys::Timer _78;
};
KSYS_CHECK_SIZE_NX150(SiteBossSpearThrow, 0x88);

}  // namespace uking::ai
