#pragma once

#include "Game/AI/Action/actionAnimalMoveGuidedBase.h"
#include "Game/AI/aiUnk_710070F974.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LynelNavMeshMove : public AnimalMoveGuidedBase {
    SEAD_RTTI_OVERRIDE(LynelNavMeshMove, AnimalMoveGuidedBase)
public:
    explicit LynelNavMeshMove(const InitArg& arg);
    ~LynelNavMeshMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x78
    sead::Vector3f* mTargetPos_d{};
    Unk_710070f974 _80;
};
KSYS_CHECK_SIZE_NX150(LynelNavMeshMove, 0x98);

}  // namespace uking::action
