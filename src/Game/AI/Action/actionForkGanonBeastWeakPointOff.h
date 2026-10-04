#pragma once

#include "Game/AI/Action/actionForkGanonBeastWeakPoint.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkGanonBeastWeakPointOff : public ForkGanonBeastWeakPoint {
    SEAD_RTTI_OVERRIDE(ForkGanonBeastWeakPointOff, ForkGanonBeastWeakPoint)
public:
    explicit ForkGanonBeastWeakPointOff(const InitArg& arg);
    ~ForkGanonBeastWeakPointOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m32(s32 point, s32 target_slot) override;
    u8 _50[0x54 - 0x50];
    int _54 = 0;
};

}  // namespace uking::action
