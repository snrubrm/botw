#pragma once

#include "Game/AI/Action/actionHorseWaitAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseWaitEx : public HorseWaitAction {
    SEAD_RTTI_OVERRIDE(HorseWaitEx, HorseWaitAction)
public:
    explicit HorseWaitEx(const InitArg& arg);
    ~HorseWaitEx() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x60
    const float* mKeepFrame_s{};
    u64 _68 = 0;
    sead::Vector3f _70 = sead::Vector3f::zero;
    u8 _7c[0x4];

};
KSYS_CHECK_SIZE_NX150(HorseWaitEx, 0x80);

}  // namespace uking::action
