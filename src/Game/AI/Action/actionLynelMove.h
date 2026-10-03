#pragma once

#include "Game/AI/Action/actionAnimalMove.h"
#include "Game/AI/aiUnk_710070F974.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LynelMove : public AnimalMove {
    SEAD_RTTI_OVERRIDE(LynelMove, AnimalMove)
public:
    explicit LynelMove(const InitArg& arg);
    ~LynelMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    bool m34(const sead::Vector3f& pos, float x) override;

    // static_param at offset 0x80
    const float* mTimeForCalcCheckCliffDist_s{};
    Unk_710070f974 _88;
};
KSYS_CHECK_SIZE_NX150(LynelMove, 0xa0);

}  // namespace uking::action
