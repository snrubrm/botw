#pragma once

#include "Game/AI/Action/actionLevelFlyMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LevelFlyMove : public LevelFlyMoveBase {
    SEAD_RTTI_OVERRIDE(LevelFlyMove, LevelFlyMoveBase)
public:
    explicit LevelFlyMove(const InitArg& arg);
    ~LevelFlyMove() override = default;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // 0x71001da0d0 (212 B) / 0x71001da1a4 (1.6 KB): declared only, called by WizzrobeVisibleWalk::calc_.
    void sub_71001DA0D0();
    void sub_71001DA1A4();

    // static_param at offset 0x138
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
