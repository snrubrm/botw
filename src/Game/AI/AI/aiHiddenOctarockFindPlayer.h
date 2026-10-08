#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HiddenOctarockFindPlayer : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HiddenOctarockFindPlayer, ksys::act::ai::Ai)
public:
    explicit HiddenOctarockFindPlayer(const InitArg& arg);
    ~HiddenOctarockFindPlayer() override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;
    // 0x7100430df0 (placeholder name)
    bool sub_7100430DF0();
    // 0x71004312d8 (placeholder name)
    void changeToNotice();
    // 0x7100430ee0 (placeholder name)
    void changeToApproaching();

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const int* mLostTimer_s{};
    // static_param at offset 0x48
    const float* mFarDist_s{};
    // static_param at offset 0x50
    const float* mActorRadius_s{};
    // static_param at offset 0x58
    const float* mLostDistOffset_s{};
    // static_param at offset 0x60
    const float* mNoticeDelayTime_s{};
    f32 _68{};
    int _6c{};
    int _70{};
    f32 _74{};
    int _78{};
    int _7c{};
};

}  // namespace uking::ai
