#pragma once

#include <math/seadVector.h>
#include <aal/aalShape.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::act {
class Actor;
class Chemical;
}

namespace ksys::map {
class Rail;
}

namespace uking::ai {

// Passed (as const void*) to ui::sub_7100A9D2B0 by ElectricCable::calc_ 0x710037c998, which fills it on the stack.
struct ElectricCableUiInfo {
    sead::Vector3f start;
    sead::Vector3f center;
    sead::Vector3f end;
    bool energized;
    ksys::act::Actor* actor;
};

class ElectricCable : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ElectricCable, ksys::act::ai::Ai)
public:
    explicit ElectricCable(const InitArg& arg);
    ~ElectricCable() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const bool* mIsDisplayOnUI_m{};
    ksys::act::Chemical* _40;
    ksys::act::Chemical* _48;
    ksys::map::Rail* _50{};
    sead::Vector3f _58 = sead::Vector3f::zero;
    sead::Vector3f _64 = sead::Vector3f::zero;
    aal::ShapeSegment* _70{};
    bool _78 = false;
};

}  // namespace uking::ai
