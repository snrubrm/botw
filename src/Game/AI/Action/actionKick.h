#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include <math/seadMatrix.h>
#include "Game/AI/aiUnk_7100D3D3A8.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class Kick : public ActionEx {
    SEAD_RTTI_OVERRIDE(Kick, ActionEx)
public:
    explicit Kick(const InitArg& arg);
    ~Kick() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // 0x71001c8818 (placeholder name): turns towards the kicked actor.
    void sub_71001C8818();
    // 0x71001c8a10 (placeholder name): applies the kick impulse to the target.
    void sub_71001C8A10();
    void calc_() override;

    // static_param at offset 0x20
    const float* mPower_s{};
    // static_param at offset 0x28
    const float* mUpRate_s{};
    // static_param at offset 0x30
    const float* mDirAngle_s{};
    // static_param at offset 0x38
    const float* mCanKickArea_s{};
    // static_param at offset 0x40
    const float* mRotSpeed_s{};
    // dynamic_param at offset 0x48
    ksys::act::BaseProcLink* mTargetActor_d{};
    bool _50 = false;
    s32 _54 = 0;
    sead::Matrix33f _58;
    ksys::VFRValue _7c;
    Unk_7100d3d3a8 _88;
};
KSYS_CHECK_SIZE_NX150(Kick, 0xa8);

}  // namespace uking::action
