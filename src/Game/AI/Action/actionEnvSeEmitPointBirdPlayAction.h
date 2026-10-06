#pragma once

#include <time/seadTickTime.h>

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EnvSeEmitPointBirdPlayAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EnvSeEmitPointBirdPlayAction, ksys::act::ai::Action)
public:
    explicit EnvSeEmitPointBirdPlayAction(const InitArg& arg);
    ~EnvSeEmitPointBirdPlayAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    sead::TickTime _20;
    s64 _28 = 0;
    sead::TickTime _30;
    s32 _38 = 0;
};
KSYS_CHECK_SIZE_NX150(EnvSeEmitPointBirdPlayAction, 0x40);

}  // namespace uking::action
