#pragma once

#include "Game/AI/Action/actionFollowChallenge.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"

namespace uking::action {

class DragonFollow : public FollowChallenge {
    SEAD_RTTI_OVERRIDE(DragonFollow, FollowChallenge)
public:
    explicit DragonFollow(const InitArg& arg);
    ~DragonFollow() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // Full F4798 reads DungeonName and sets this action's dungeon position.
    void sub_71000F4798();

    // static_param at offset 0xab0
    sead::SafeString mDungeonName_s{};

    // Members not recovered yet (class size from the factory).
    u8 _ac0[0xb98 - 0xac0];
    // F4534 constructs ModelBindInfo here; F460C destroys its bone key/link,
    // and F49B0 uses its ActorBind interface before leave_ unbinds it.
    ksys::act::ModelBindInfo mBindInfo;
    // F4534 initializes these; F4798 writes the position and F49B0 consumes all three.
    u32 _c38 = 3;
    sead::Vector3f mDungeonPosition = sead::Vector3f::zero;
    s32 _c48 = 0;
};
KSYS_CHECK_SIZE_NX150(DragonFollow, 0xc50);

}  // namespace uking::action
