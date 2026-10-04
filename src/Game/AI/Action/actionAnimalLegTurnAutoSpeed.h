#pragma once

#include "KingSystem/ActorSystem/actBoneHandle.h"
#include "Game/AI/Action/actionForkAnimalASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnimalLegTurnAutoSpeed : public ForkAnimalASPlay {
    SEAD_RTTI_OVERRIDE(AnimalLegTurnAutoSpeed, ForkAnimalASPlay)
public:
    explicit AnimalLegTurnAutoSpeed(const InitArg& arg);
    ~AnimalLegTurnAutoSpeed() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x710008fac0 (declared only): out of line in the original.
    void sub_710008FAC0();
    void calc_() override;

    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    f32 _68 = 0.0f;
    f32 _6c = 0.0f;
    f32 _70 = 0.0f;
    u8 _74[0x4];
    ksys::act::Actor* _78 = mActor;
    s32 _80 = 0;
    bool _84 = false;
    u8 _85[0x63];
    ksys::act::BoneHandle _e8;
    u8 _190[0x24];
    bool _1b4 = false;
    u8 _1b5[0x3];
    u64 _1b8 = 0;
    u32 _1c0 = 0;
    f32 _1c4 = 0.0f;
};
KSYS_CHECK_SIZE_NX150(AnimalLegTurnAutoSpeed, 0x1c8);

}  // namespace uking::action
