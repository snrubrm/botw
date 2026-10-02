#pragma once

#include "Game/AI/Action/actionUnk_7102451ba0.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class JumpTackle : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(JumpTackle, ksys::act::ai::Action)
public:
    explicit JumpTackle(const InitArg& arg);
    ~JumpTackle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();
    virtual void m33();
    virtual bool m34();

    // static_param at offset 0x20
    const float* mMaxSpeed_s{};
    // static_param at offset 0x28
    const float* mMinSpeed_s{};
    // static_param at offset 0x30
    const float* mJumpHeight_s{};
    // static_param at offset 0x38
    const float* mJumpHeightMaxOffset_s{};
    // static_param at offset 0x40
    const bool* mIsFinishedAtPreLandFrame_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
    Unk_7102451ba0 _50;
    ksys::VFRValue _78;
    // unknown (not accessed by JumpTackle or its subclasses)
    u8 _84[0x90 - 0x84];
    bool _90 = false;
    bool _91 = false;
};

}  // namespace uking::action
