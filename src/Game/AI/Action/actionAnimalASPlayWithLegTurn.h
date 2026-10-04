#pragma once

#include "KingSystem/ActorSystem/actBoneHandle.h"
#include "Game/AI/Action/actionForkAnimalASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnimalASPlayWithLegTurn : public ForkAnimalASPlay {
    SEAD_RTTI_OVERRIDE(AnimalASPlayWithLegTurn, ForkAnimalASPlay)
public:
    explicit AnimalASPlayWithLegTurn(const InitArg& arg);
    ~AnimalASPlayWithLegTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x710008dc24 (declared only): out of line in the original.
    void sub_710008DC24();
    void calc_() override;

    struct Params {
        // static_param at offset 0x60
        const float* mRotSpeed_s{};
        // static_param at offset 0x68
        const float* mRotAccRatio_s{};
        // static_param at offset 0x70
        const float* mRotRatio_s{};
        // dynamic_param at offset 0x78
        sead::Vector3f* mTargetPos_d{};
    };
    Params mParams;
    ksys::act::Actor* _80 = mActor;
    s32 _88 = 0;
    bool _8c = false;
    u8 _8d[0x63];
    ksys::act::BoneHandle _f0;
    bool _198 = false;
    u8 _199[3];
    f32 _19c = 0.0f;
    f32 _1a0 = 0.0f;
    u8 _1a4[0x24];
};
KSYS_CHECK_SIZE_NX150(AnimalASPlayWithLegTurn, 0x1c8);

}  // namespace uking::action
