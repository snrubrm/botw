#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PlayerItem : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PlayerItem, ksys::act::ai::Ai)
public:
    explicit PlayerItem(const InitArg& arg);

    bool isFinished() const override;
    bool isChangeable() const override;
    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
