#pragma once

#include <math/seadMatrix.h>
#include "Game/AI/aiUnk_71010C3588.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkCapsuleWindFollow : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkCapsuleWindFollow, ksys::act::ai::Action)
public:
    explicit ForkCapsuleWindFollow(const InitArg& arg);
    ~ForkCapsuleWindFollow() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool hasUpdateForPreDeleteCb() override;
    bool updateForPreDelete() override;

protected:
    void calc_() override;

    // 0x7100149878: the shortest-arc rotation from `from` to `to` as a matrix (identity if they are opposite);
    // false in that case.
    static bool sub_7100149878(sead::Matrix33f* mtx, const sead::Vector3f& from, const sead::Vector3f& to);

    // static_param at offset 0x20
    const float* mRadius_s{};
    // static_param at offset 0x28
    const float* mSpeed_s{};
    // static_param at offset 0x30
    const float* mLength_s{};
    // static_param at offset 0x38
    const sead::Vector3f* mDir_s{};
    /* 0x40 */ Unk_710250c3c8 _40;
    /* 0xc8 */ sead::Matrix33f _c8;
    /* 0xec */ f32 _ec;
};

}  // namespace uking::action
