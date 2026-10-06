#pragma once

#include <container/seadObjList.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

namespace uking::action {

class SwarmGullMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SwarmGullMove, ksys::act::ai::Action)
public:
    explicit SwarmGullMove(const InitArg& arg);
    ~SwarmGullMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    sead::SafeString mASName_s{};
    // map_unit_param at offset 0x30
    const int* mSubUnitNum_m{};
    // map_unit_param at offset 0x38
    const float* mCreateMaxRadius_m{};
    // map_unit_param at offset 0x40
    const float* mCreateMinRadius_m{};
    // map_unit_param at offset 0x48
    const float* mCreateHeightRange_m{};
    // map_unit_param at offset 0x50
    const float* mRoundMaxRadius_m{};
    // map_unit_param at offset 0x58
    const float* mRoundMinRadius_m{};
    // map_unit_param at offset 0x60
    const float* mCrySoundIntervalMin_m{};
    // map_unit_param at offset 0x68
    const float* mCrySoundIntervalMax_m{};
    struct Gull {
        ksys::act::BaseProcHandle _0;
        void* _10 = nullptr;
        s32 _18 = -1;
    };
    Gull _70[10];
    sead::ObjList<sead::Vector3f> _1b0;
    s32 _1e0 = 0;
};

}  // namespace uking::action
