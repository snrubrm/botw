#pragma once

#include "Game/AI/Action/actionGetUpBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GetUpLinear : public GetUpBase {
    SEAD_RTTI_OVERRIDE(GetUpLinear, GetUpBase)
public:
    explicit GetUpLinear(const InitArg& arg);
    ~GetUpLinear() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m32(ksys::phys::CharacterController* controller) override;
    bool m33() override;
    bool m34() override;

    // static_param at offset 0x148
    const sead::Vector3f* mRotCenterPos_s{};
    f32 _150 = 0;
    sead::Vector3f _154;
};

}  // namespace uking::action
