#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class FreeMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(FreeMove, ksys::act::ai::Action)
public:
    explicit FreeMove(const InitArg& arg);
    ~FreeMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;
    virtual bool m32(ksys::phys::CharacterController* controller);
    virtual void m33(ksys::phys::CharacterController* controller);
    virtual bool m34();
    virtual bool m35();
    virtual f32 m36();
    virtual void m37(f32 speed, ksys::phys::CharacterController* controller);
    // 0x710016b114: sets both values of _34 (out of line in the original, called from subclasses).
    void sub_710016B114(f32 value);

    sead::Vector3f _1c;
    sead::Vector3f _28;
    ksys::VFRValue _34;
    int _40 = 0;
    u32 _44 = 0;
    u32 _48 = 0;
    u32 _4c = 0;
    u32 _50 = 0;
    u32 _54 = 0;
    u32 _58 = 0;
    struct Params {
        // static_param at offset 0x60
        const float* mSpeed_s{};
        // static_param at offset 0x68
        const float* mSpeedAddRate_s{};
        // static_param at offset 0x70
        const float* mAngleSpeed_s{};
        // static_param at offset 0x78
        const bool* mIsChangeable_s{};
        // static_param at offset 0x80
        const bool* mIsIgnoreSameAS_s{};
        // static_param at offset 0x88
        const bool* mAllowPitchRotation_s{};
        // static_param at offset 0x90
        sead::SafeString mASKeyName_s{};
    };
    Params mParams;
    ksys::act::MotionType _a0{};
};

}  // namespace uking::action
