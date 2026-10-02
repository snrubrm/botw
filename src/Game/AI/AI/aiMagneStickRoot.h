#pragma once

#include <math/seadMathCalcCommon.h>

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class MagneStickRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MagneStickRoot, ksys::act::ai::Ai)
public:
    explicit MagneStickRoot(const InitArg& arg);
    ~MagneStickRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual f32 m42();
    virtual void m43();
    virtual void m44();
    virtual void m45();
    virtual void m46();
    virtual void m47();
    virtual void m48();
    virtual void m49();
    virtual void m50() {}
    virtual void m51() {}

protected:
    u32 _38 = 0;
    // static_param at offset 0x40
    const float* mDefaultConnectionDistance_s{};
    // static_param at offset 0x48
    const float* mCollideRadiusFactor_s{};
    // map_unit_param at offset 0x50
    const float* mCollideRadius_m{};
    // map_unit_param at offset 0x58
    const bool* mJoinSystemGroup_m{};
    // map_unit_param at offset 0x60
    const bool* mRegistFromBeginning_m{};
    // map_unit_param at offset 0x68
    const bool* mIgnoreObstacle_m{};
    // aitree_variable at offset 0x70
    bool* mIsTargetFixedAcceptor_a{};
    bool _78 = false;
    bool _79 = false;
    u32 _7c = 0;
    f32 _80 = 0.0f;
    f32 _84 = 0.0f;
    f32 _88 = sead::Mathf::maxNumber();
    ksys::Timer _8c;
    u32 _98 = 0;
    u32 _9c = 0;
};

}  // namespace uking::ai
