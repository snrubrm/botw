#pragma once

#include "Game/Actor/aiUnk_71025b1808.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RegistedActorSetActionBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RegistedActorSetActionBase, ksys::act::ai::Action)
public:
    explicit RegistedActorSetActionBase(const InitArg& arg);
    ~RegistedActorSetActionBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;
    bool handleAck_(const ksys::MessageAck* ack) override;

protected:
    void calc_() override;

    Unk_71025b1808Data _20;
    // static_param at offset 0x400
    const bool* mTeachSelfRegistedActor_s{};
};

}  // namespace uking::action
