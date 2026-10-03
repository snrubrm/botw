#pragma once

#include "Game/AI/Action/actionBeamMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianMiniBeamMove : public BeamMove {
    SEAD_RTTI_OVERRIDE(GuardianMiniBeamMove, BeamMove)
public:
    explicit GuardianMiniBeamMove(const InitArg& arg);
    ~GuardianMiniBeamMove() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x70
    const float* mReboundDeccel_s{};
    u64 _78 = 0;
    u64 _80 = 0;
    u64 _88 = 0;
    u64 _90 = 0;
    s32 _98 = -1;
    u8 _9c[0x4];

};
KSYS_CHECK_SIZE_NX150(GuardianMiniBeamMove, 0xa0);

}  // namespace uking::action
