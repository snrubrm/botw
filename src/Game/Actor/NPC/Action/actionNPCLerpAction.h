#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/Utils/Types.h"

namespace uking::action {

class NPCLerpAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCLerpAction, ksys::act::ai::Action)
public:
    explicit NPCLerpAction(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual const char* m32();

    // static_param at offset 0x20
    const float* mRotateSpeed_s{};
    // static_param at offset 0x28
    const float* mArriveDist_s{};
    // static_param at offset 0x30
    const bool* mIsRotateByRot_s{};
    // static_param at offset 0x38
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetRot_d{};
    sead::Vector3f _58 = sead::Vector3f::zero;
    bool _64 = false;
    bool _65 = false;
    sead::Vector3f _68;
    sead::Vector3f _74{0, 0, 0};
    ksys::VFRVec3f _80;
};
KSYS_CHECK_SIZE_NX150(NPCLerpAction, 0xa8);

}  // namespace uking::action
