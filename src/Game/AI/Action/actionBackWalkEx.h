#pragma once

#include "Game/AI/Action/actionBackWalkBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"

namespace ksys::phys {
class CharacterController;
}

namespace uking::action {

class BackWalkEx : public BackWalkBase {
    SEAD_RTTI_OVERRIDE(BackWalkEx, BackWalkBase)
public:
    explicit BackWalkEx(const InitArg& arg);
    ~BackWalkEx() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32(ksys::phys::CharacterController* controller);
    virtual void m33(ksys::phys::CharacterController* controller);

    ksys::VFRValue _b0{0.0f};
};

}  // namespace uking::action
