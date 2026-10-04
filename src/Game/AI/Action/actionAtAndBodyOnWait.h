#pragma once

#include "Game/AI/Action/actionAtOnWait.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::phys {
class RigidBody;
}

namespace uking::action {

class AtAndBodyOnWait : public AtOnWait {
    SEAD_RTTI_OVERRIDE(AtAndBodyOnWait, AtOnWait)
public:
    explicit AtAndBodyOnWait(const InitArg& arg);
    ~AtAndBodyOnWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x71000504e8 (declared only): finds the body `name` of the actor.
    ksys::phys::RigidBody* sub_71000504E8(const sead::SafeString& name);
    void calc_() override;

    // static_param at offset 0x28
    sead::SafeString mBodyName_s{};
};

}  // namespace uking::action
