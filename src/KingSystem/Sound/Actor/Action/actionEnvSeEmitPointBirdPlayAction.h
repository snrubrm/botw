#pragma once

#include <time/seadTickTime.h>

#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::snd {

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
    // Complete FEA4E4 and independent calc FEA288 return the playback rate.
    f32 sub_7100FEA4E4();
    sead::TickTime _20;
    sead::TickSpan _28;
    sead::TickTime _30;
    s32 _38 = 0;
};
KSYS_CHECK_SIZE_NX150(EnvSeEmitPointBirdPlayAction, 0x40);

}  // namespace ksys::snd
