#pragma once

#include "Game/Actor/Action/actionTurnToActor.h"
#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::action {

class DemoTurnToActor : public TurnToActor {
    SEAD_RTTI_OVERRIDE(DemoTurnToActor, TurnToActor)
public:
    explicit DemoTurnToActor(const InitArg& arg);
    ~DemoTurnToActor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    sead::Matrix34f m33() override;
    void sub_71000EBE30(ksys::act::BaseProcLink* link, const sead::SafeString& name,
                       const sead::SafeString& unique_name);

    // dynamic_param at offset 0x60
    sead::SafeString mActorName_d{};
    // dynamic_param at offset 0x70
    sead::SafeString mUniqueName_d{};

    /* 0x80 */ ksys::act::BaseProcLink _80;
    /* 0x90 */ sead::Matrix34f _90;
};

}  // namespace uking::action
