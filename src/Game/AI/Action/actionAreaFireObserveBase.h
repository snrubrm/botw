#pragma once

#include "Game/AI/Action/actionActorObserverBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaFireObserveBase : public ksys::act::ai::Action, public Unk_71024e5408 {
    SEAD_RTTI_OVERRIDE(AreaFireObserveBase, ksys::act::ai::Action)
public:
    explicit AreaFireObserveBase(const InitArg& arg);
    ~AreaFireObserveBase() override = default;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    void calc_() override;
};
KSYS_CHECK_SIZE_NX150(AreaFireObserveBase, 0x50);

}  // namespace uking::action
