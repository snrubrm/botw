#pragma once

#include <time/seadTickTime.h>

#include "KingSystem/ActorSystem/actAiAction.h"

namespace xlink2 {
class HandleSLink;
}

namespace uking::action {

class EnvSeEmitPointInsectPlayAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EnvSeEmitPointInsectPlayAction, ksys::act::ai::Action)
public:
    explicit EnvSeEmitPointInsectPlayAction(const InitArg& arg);
    ~EnvSeEmitPointInsectPlayAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    s32 _1c = -1;
    f32 _20 = -1.0f;
    u32 _24 = 0;
    xlink2::HandleSLink* _28 = nullptr;
    sead::TickTime _30;
    bool _38 = false;
};
KSYS_CHECK_SIZE_NX150(EnvSeEmitPointInsectPlayAction, 0x40);

}  // namespace uking::action
