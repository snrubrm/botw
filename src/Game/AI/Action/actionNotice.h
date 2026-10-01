#pragma once

#include "Game/AI/Action/actionActionWithAS.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Notice : public ActionWithAS {
    SEAD_RTTI_OVERRIDE(Notice, ActionWithAS)
public:
    explicit Notice(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    bool isChangeable() const override;

protected:
};

}  // namespace uking::action
