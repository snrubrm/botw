#pragma once

#include "Game/Actor/Action/actionAvoidingCloseMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class AvoidingCloseMoveActionBase : public AvoidingCloseMoveBase {
    SEAD_RTTI_OVERRIDE(AvoidingCloseMoveActionBase, AvoidingCloseMoveBase)
public:
    explicit AvoidingCloseMoveActionBase(const InitArg& arg);
    ~AvoidingCloseMoveActionBase() override;

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
