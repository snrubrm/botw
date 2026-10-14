#pragma once

#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/System/VFRValue.h"
#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GanonFallAttack : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GanonFallAttack, ksys::act::ai::Action)
public:
    explicit GanonFallAttack(const InitArg& arg);
    ~GanonFallAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mIsEmitShockWave_s{};
    // dynamic_param at offset 0x28
    sead::Vector3f* mTargetPos_d{};
    u16 _30 = 0;
    u8 _32[0xe];
    ksys::VFRValue _40;
    sead::Matrix33f _4c;
    ksys::act::BaseProcHandle _70;
};
KSYS_CHECK_SIZE_NX150(GanonFallAttack, 0x80);

}  // namespace uking::action
