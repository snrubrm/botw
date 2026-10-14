#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WarpToPos : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WarpToPos, ksys::act::ai::Action)
public:
    explicit WarpToPos(const InitArg& arg);
    ~WarpToPos() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;
    bool oneShot_() override;

protected:
    // dynamic_param at offset 0x20
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x28
    sead::Vector3f* mTargetRot_d{};
    /* 0x30 */ sead::Matrix34f _30 = sead::Matrix34f::ident;
    /* 0x60 */ sead::Vector3f _60 = sead::Vector3f::ones;
};
KSYS_CHECK_SIZE_NX150(WarpToPos, 0x70);

}  // namespace uking::action
