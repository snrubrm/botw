#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ElectricCable : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ElectricCable, ksys::act::ai::Ai)
public:
    explicit ElectricCable(const InitArg& arg);
    ~ElectricCable() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const bool* mIsDisplayOnUI_m{};
    void* _40{};
    void* _48{};
    void* _50{};
    sead::Vector3f _58 = sead::Vector3f::zero;
    sead::Vector3f _64 = sead::Vector3f::zero;
    // aal::ShapeSegment* (created in init_ with aal::ShapeSegment::create)
    void* _70{};
    bool _78 = false;
};

}  // namespace uking::ai
