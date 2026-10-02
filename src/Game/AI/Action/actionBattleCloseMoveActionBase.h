#pragma once

#include "Game/AI/Action/actionBattleCloseAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class BattleCloseMoveActionBase : public BattleCloseAction {
    SEAD_RTTI_OVERRIDE(BattleCloseMoveActionBase, BattleCloseAction)
public:
    explicit BattleCloseMoveActionBase(const InitArg& arg);
    ~BattleCloseMoveActionBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    bool m37(ksys::phys::CharacterController* controller, f32 speed,
             const sead::Vector3f& dir) override;

    ksys::VFRValue _98;
};

}  // namespace uking::action
