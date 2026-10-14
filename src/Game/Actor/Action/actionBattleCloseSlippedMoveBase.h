#pragma once

#include "Game/Actor/Action/actionAvoidingCloseMoveActionWithAcc.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleCloseSlippedMoveBase : public AvoidingCloseMoveActionWithAcc {
    SEAD_RTTI_OVERRIDE(BattleCloseSlippedMoveBase, AvoidingCloseMoveActionWithAcc)
public:
    explicit BattleCloseSlippedMoveBase(const InitArg& arg);
    ~BattleCloseSlippedMoveBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    ksys::act::Unk_7100d78e50* m33(int idx) override;
    bool m34(ksys::act::Unk_7100d78e50* entry) override;
};

}  // namespace uking::action
