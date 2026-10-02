#pragma once

#include "Game/AI/aiUnk_7102357d20.h"
#include "Game/AI/Action/actionAreaObserveActorAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CallOvserveActorTag : public AreaObserveActorAction {
    SEAD_RTTI_OVERRIDE(CallOvserveActorTag, AreaObserveActorAction)
public:
    explicit CallOvserveActorTag(const InitArg& arg);
    ~CallOvserveActorTag() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
    void calc_() override;
    bool m15(const ksys::act::ActorConstDataAccess& accessor) override;

    Unk_710236f520 _98{mActor, 0x8000007};
};
KSYS_CHECK_SIZE_NX150(CallOvserveActorTag, 0xc8);

}  // namespace uking::action
