#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include <container/seadSafeArray.h>
#include <math/seadVector.h>

namespace uking::ai {

class KorokGoalTimerRootAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(KorokGoalTimerRootAI, ksys::act::ai::Ai)
public:
    explicit KorokGoalTimerRootAI(const InitArg& arg);
    ~KorokGoalTimerRootAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const float* mGoalCountLimit_m{};
    // calc_ uses the scale at +0x40 and the XLink handle pair at +0x50,
    // repeated ten times at a stride of 0x30.
    struct EffectState {
        float scale;
        u8 _4[12];
        Unk_71012419b4 handles;
    };
    sead::SafeArray<EffectState, 10> mEffects;
    u32 _220 = 0;
    bool _224 = false;
    bool _225 = true;
    bool _226 = false;
    float _228 = 0;
    float _22c = 0;
    sead::Vector3f _230 = sead::Vector3f::zero;
    s32 _23c = 0;
    sead::Vector3f _240 = sead::Vector3f::zero;
    sead::Vector3f _24c = sead::Vector3f::zero;
    sead::Vector3f _258 = sead::Vector3f::zero;
    float _264 = 0;
    float _268 = 0;
    bool _26c = false;
    Unk_71012419b4 _270;
    Unk_71012419b4 _290;
    Unk_71012419b4 _2b0;
};

}  // namespace uking::ai
