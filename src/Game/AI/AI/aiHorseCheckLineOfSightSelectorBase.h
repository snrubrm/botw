#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::phys {
class NavMeshCharacter;
}

namespace uking::ai {

class HorseCheckLineOfSightSelectorBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HorseCheckLineOfSightSelectorBase, ksys::act::ai::Ai)
public:
    explicit HorseCheckLineOfSightSelectorBase(const InitArg& arg);
    ~HorseCheckLineOfSightSelectorBase() override;
    bool isFailed() const override;
    bool isFinished() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34(sead::Vector3f* out);

    // 0x7100346aa4 (placeholder name): line-of-sight probe in one direction.
    bool sub_7100346AA4(ksys::phys::NavMeshCharacter* nav, sead::Vector3f* dir);

protected:
    // static_param at offset 0x38
    const int* mDirectionNum_s{};
    // static_param at offset 0x40
    const float* mDirectionAngle_s{};
    // static_param at offset 0x48
    const float* mDistance_s{};
    // static_param at offset 0x50
    const float* mRadiusScale_s{};
};

}  // namespace uking::ai
