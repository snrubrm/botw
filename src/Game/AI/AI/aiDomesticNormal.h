#pragma once

#include <limits>
#include <math/seadVector.h>
#include "Game/AI/AI/aiPreyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace ksys::map {
class Rail;
}

namespace uking::ai {

class DomesticNormal : public PreyNormal {
    SEAD_RTTI_OVERRIDE(DomesticNormal, PreyNormal)
public:
    explicit DomesticNormal(const InitArg& arg);
    ~DomesticNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void calc_() override;
    void loadParams_() override;

    // Slot 44 (PreyNormal ends at m43): true in the escape / notice / look / interest / target
    // notice / last resort states.
    virtual bool m44();

protected:
    bool sub_7100364F7C();
    void sub_71003653B0();
    bool sub_710036550C(f32* angle);

    // static_param at offset 0x340
    const int* mWaitFramesAfterRunMax_s{};
    // static_param at offset 0x348
    const int* mNumFailPathHomeFadeout_s{};
    // static_param at offset 0x350
    const float* mDistUntilReturnToHomePos_s{};
    // static_param at offset 0x358
    const float* mWaitFramesAfterRunMin_s{};
    // static_param at offset 0x360
    const float* mStaggerVelocityThreshold_s{};
    // static_param at offset 0x368
    const float* mDistHomePosFadeout_s{};
    // aitree_variable at offset 0x370
    sead::SafeString* mDomesticAnimalRailName_a{};
    ksys::map::Rail* _378 = nullptr;  // rail of the map object / named rail (0x7100364f7c)
    sead::Vector3f _380{std::numeric_limits<f32>::quiet_NaN(),
                        std::numeric_limits<f32>::quiet_NaN(),
                        std::numeric_limits<f32>::quiet_NaN()};
    ksys::Timer _38c{0, 0};
    s8 _398 = 0;
    bool _399 = false;
};
KSYS_CHECK_SIZE_NX150(DomesticNormal, 0x3a0);

}  // namespace uking::ai
