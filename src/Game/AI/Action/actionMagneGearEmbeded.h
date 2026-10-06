#pragma once

#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::phys {
class Constraint;
}

namespace uking::action {

class MagneGearEmbeded : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(MagneGearEmbeded, ksys::act::ai::Action)
public:
    explicit MagneGearEmbeded(const InitArg& arg);
    ~MagneGearEmbeded() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    ksys::phys::Constraint* _20{};
    ksys::phys::Constraint* _28{};
    ksys::phys::Constraint* _30{};
    ksys::phys::Constraint* _38{};
    ksys::phys::Constraint* _40{};
    xlink2::HandleSLink* _48{};
};

}  // namespace uking::action
