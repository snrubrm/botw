#pragma once

#include "Game/AI/aiUnk_7102384718.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkASTrgTurnGround : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkASTrgTurnGround, ksys::act::ai::Action)
public:
    explicit ForkASTrgTurnGround(const InitArg& arg);
    ~ForkASTrgTurnGround() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mSpeedBasePosRatio_s{};
    // static_param at offset 0x28
    const float* mOnAfterGroundRotAngle_s{};
    // static_param at offset 0x30
    const sead::Vector3f* mAxis_s{};
    // static_param at offset 0x38
    const sead::Vector3f* mCtrlOffset_s{};
    // static_param at offset 0x40
    const sead::Vector3f* mCtrlAngleOffset_s{};
    // static_param at offset 0x48
    const sead::Vector3f* mActMoveVec_s{};
    // aitree_variable at offset 0x50
    void* mCRBOffsetUnit_a{};
    Unk_71000b0800<Unk_7102384718> _58;
    u8 _60[0x30];
    s32 _90 = 0;
    bool _94 = false;
    u8 _95[0x3];
    f32 _98 = 1.0f;
    sead::Vector3f _9c = sead::Vector3f::zero;
};
KSYS_CHECK_SIZE_NX150(ForkASTrgTurnGround, 0xa8);

}  // namespace uking::action
