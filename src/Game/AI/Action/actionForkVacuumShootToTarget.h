#pragma once

#include "Game/AI/aiUnk_710073EBD4.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkVacuumShootToTarget : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkVacuumShootToTarget, ksys::act::ai::Action)
public:
    explicit ForkVacuumShootToTarget(const InitArg& arg);
    ~ForkVacuumShootToTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();

    /* 0x20 */ Unk_710073ebd4 _20{mActor};
    // static_param at offset 0xc8
    const bool* mIsReuseBullet_s{};
};

}  // namespace uking::action
