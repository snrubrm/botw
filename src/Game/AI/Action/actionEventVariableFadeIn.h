#pragma once

#include "Game/AI/Action/actionEventVariableFade.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventVariableFadeIn : public EventVariableFade {
    SEAD_RTTI_OVERRIDE(EventVariableFadeIn, EventVariableFade)
public:
    explicit EventVariableFadeIn(const InitArg& arg);
    ~EventVariableFadeIn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool _40 = false;
    u8 _41[0x7];

};
KSYS_CHECK_SIZE_NX150(EventVariableFadeIn, 0x48);

}  // namespace uking::action
