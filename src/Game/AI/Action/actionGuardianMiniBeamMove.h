#pragma once

#include "Game/AI/Action/actionBeamMove.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
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
    int m43() override { return 1; }
    void calc_() override;
    f32 m37() override { return *mReboundDeccel_s; }

    // static_param at offset 0x70
    const float* mReboundDeccel_s{};
    Unk_71012419b4 _78;
    s32 _98 = -1;
    u8 _9c[0x4];

};
KSYS_CHECK_SIZE_NX150(GuardianMiniBeamMove, 0xa0);

}  // namespace uking::action
