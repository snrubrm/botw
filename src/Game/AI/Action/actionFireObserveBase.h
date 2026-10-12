#pragma once

#include "Game/AI/Action/actionActorObserverBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FireObserveBase : public ksys::act::ai::Action, public Unk_71024e5408 {
    SEAD_RTTI_OVERRIDE(FireObserveBase, ksys::act::ai::Action)
public:
    explicit FireObserveBase(const InitArg& arg);
    ~FireObserveBase() override = default;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    void calc_() override;
};
KSYS_CHECK_SIZE_NX150(FireObserveBase, 0x50);

}  // namespace uking::action
