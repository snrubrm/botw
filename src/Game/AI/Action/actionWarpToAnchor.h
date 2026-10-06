#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WarpToAnchor : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WarpToAnchor, ksys::act::ai::Action)
public:
    explicit WarpToAnchor(const InitArg& arg);
    ~WarpToAnchor() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;
    bool oneShot_() override;

protected:
    virtual void m32();

    // dynamic_param at offset 0x20
    float* mDirectionY_d{};
    // dynamic_param at offset 0x28
    float* mDestinationY_d{};
    // dynamic_param at offset 0x30
    float* mDestinationZ_d{};
    // dynamic_param at offset 0x38
    float* mDestinationX_d{};
    sead::Matrix34f _40 = sead::Matrix34f::ident;
    sead::Vector3f _70 = sead::Vector3f::ones;
};

}  // namespace uking::action
