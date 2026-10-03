#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include <math/seadVector.h>

namespace ksys::phys {
class CharacterController;
}

namespace uking::action {

class PlayerTurnInner : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerTurnInner, PlayerAction)
public:
    explicit PlayerTurnInner(const InitArg& arg);
    ~PlayerTurnInner() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;
    virtual void m33();
    virtual void m34();
    virtual void m35(ksys::phys::CharacterController* controller);

    sead::Vector3f _20 = sead::Vector3f::zero;
};

}  // namespace uking::action
