#pragma once

#include <math/seadMatrix.h>
#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"

namespace ksys::phys {
class CharacterController;
}

namespace uking::action {

class NavMeshAction : public ActionEx {
    SEAD_RTTI_OVERRIDE(NavMeshAction, ActionEx)
public:
    explicit NavMeshAction(const InitArg& arg);
    // The original keeps this destructor out of line next to the subclasses' inlined copies, which a
    // defaulted destructor does not. Written like upstream's GameDataFlagSelector::~GameDataFlagSelector()
    // { ; } (commit 96101229).
    ~NavMeshAction() override { ; }

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();
    virtual void m33();
    virtual void m34() = 0;
    virtual sead::Vector3f* m35();
    virtual void m36(ksys::phys::CharacterController* controller, f32 speed,
                     const sead::Vector3f& up);
    virtual void m37(const sead::Matrix34f& mtx);

    struct Params {
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
    };
    Params mParams;
    ksys::VFRValue _60{0.0f};
    sead::Matrix33f _6c;
    void* _90 = nullptr;
    f32 _98 = -1.0f;
    f32 _9c = 0.0f;
    f32 _a0 = 0.0f;
};

KSYS_CHECK_SIZE_NX150(NavMeshAction, 0xa8);

}  // namespace uking::action
