#pragma once

#include "Game/AI/Action/actionNPCTurnToObject.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCTurnToObjectGreeting : public NPCTurnToObject {
    SEAD_RTTI_OVERRIDE(NPCTurnToObjectGreeting, NPCTurnToObject)
public:
    explicit NPCTurnToObjectGreeting(const InitArg& arg);
    ~NPCTurnToObjectGreeting() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x710020adf0 (declared only, 828 B): runs for GreetingType 1 / 6 (NPCTurnToObject::_40) at the end of enter_.
    void sub_710020ADF0();
    void calc_() override;

    // dynamic_param at offset 0x68
    sead::SafeString mGreetingType_d{};
};

}  // namespace uking::action
