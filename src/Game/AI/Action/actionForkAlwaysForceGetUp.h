#pragma once

#include "Game/AI/aiUnk_71000b0800.h"
#include "Game/AI/aiUnk_7102384718.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkAlwaysForceGetUp : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkAlwaysForceGetUp, ksys::act::ai::Action)
public:
    explicit ForkAlwaysForceGetUp(const InitArg& arg);
    ~ForkAlwaysForceGetUp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // Writes the (unit) direction the actor should turn to (0x7100137... m32, not decompiled).
    virtual void m32(sead::Vector3f* dir);

    // aitree_variable at offset 0x20
    void* mCRBOffsetUnit_a{};
    // static_param at offset 0x28
    const float* mRotRatio_s{};
    // static_param at offset 0x30
    const float* mRotSpdMin_s{};
    // static_param at offset 0x38
    const float* mRotSpdMax_s{};
    // static_param at offset 0x40
    const bool* mIsUseCRBOffsetUnit_s{};
    u8 _48[0x78 - 0x48];
    Unk_71000b0800<Unk_7102384718> _78;
    bool _80{};
};

}  // namespace uking::action
