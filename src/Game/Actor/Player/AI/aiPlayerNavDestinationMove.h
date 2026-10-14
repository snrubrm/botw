#pragma once

#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PlayerNavDestinationMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PlayerNavDestinationMove, ksys::act::ai::Ai)
public:
    explicit PlayerNavDestinationMove(const InitArg& arg);
    ~PlayerNavDestinationMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;

protected:
    // Out-of-line helpers (0x710082df0c / 0x710082e048 / 0x710082e38c; placeholder names): change to the child
    // with the destination / stick values packed.
    void sub_710082DF0C();
    void sub_710082E048();
    void sub_710082E38C();

    // dynamic_param at offset 0x38
    float* mDestPosX_d{};
    // dynamic_param at offset 0x40
    float* mDestPosY_d{};
    // dynamic_param at offset 0x48
    float* mDestPosZ_d{};
    // dynamic_param at offset 0x50
    float* mStickValue_d{};
    // An embedded copy of Enemy's navmesh character wrapper (see Enemy::Unk_12d0); `_8` is the state here.
    uking::act::Enemy::Unk_12d0 _58{nullptr, -1, 0};
};
KSYS_CHECK_SIZE_NX150(PlayerNavDestinationMove, 0x78);

}  // namespace uking::ai
