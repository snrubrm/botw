#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class NavMeshAction : public ActionEx {
    SEAD_RTTI_OVERRIDE(NavMeshAction, ActionEx)
public:
    explicit NavMeshAction(const InitArg& arg);
    ~NavMeshAction() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();
    virtual void m33();
    virtual void m34() = 0;

    // static_param at offset 0x20
    const int* mWeaponIdx_s{};
    // static_param at offset 0x28
    const float* mSpeed_s{};
    // static_param at offset 0x30
    const float* mRotSpd_s{};
    // static_param at offset 0x38
    const float* mFinRadius_s{};
    // static_param at offset 0x40
    const float* mFinRotate_s{};
    // static_param at offset 0x48
    const float* mAccRatio_s{};
    // static_param at offset 0x50
    const bool* mIsCheckCliff_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    ksys::VFRValue _60{0.0f};
    // unknown object (0x24 bytes; same type as TurnBase::_6c, methods 0x7100741034...)
    u8 _6c[0x90 - 0x6c];
    void* _90 = nullptr;
    f32 _98 = -1.0f;
    u32 _9c = 0;
    u32 _a0 = 0;
};

KSYS_CHECK_SIZE_NX150(NavMeshAction, 0xa8);

}  // namespace uking::action
