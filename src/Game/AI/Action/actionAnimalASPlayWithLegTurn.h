#pragma once

#include "Game/AI/aiUnk_710070E434.h"
#include "Game/AI/Action/actionForkAnimalASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::phys {
class CharacterController;
}

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
    // 0x710008df6c (declared only)
    void sub_710008DF6C(ksys::phys::CharacterController* controller);
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
    Unk_710070e434 _80{mActor};
    u8 _198 = 0;
    u8 _199[3];
    f32 _19c = 0.0f;
    f32 _1a0 = 0.0f;
    sead::Matrix33f _1a4;
};
KSYS_CHECK_SIZE_NX150(AnimalASPlayWithLegTurn, 0x1c8);

}  // namespace uking::action
