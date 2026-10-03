#pragma once

#include "Game/AI/aiUnk_71025b0578.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LynelBreathMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LynelBreathMove, ksys::act::ai::Action)
public:
    explicit LynelBreathMove(const InitArg& arg);
    ~LynelBreathMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    sead::Vector3f _1c;
    Unk_7100716408 _28;
    bool _d0 = true;
    u8 _d1[0x7];

};
KSYS_CHECK_SIZE_NX150(LynelBreathMove, 0xd8);

}  // namespace uking::action
