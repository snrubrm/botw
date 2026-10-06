#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WizzrobeRoam : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WizzrobeRoam, ksys::act::ai::Ai)
public:
    explicit WizzrobeRoam(const InitArg& arg);
    ~WizzrobeRoam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x71005fe5cc: counts the move, picks the next position (sub_71005FEB18) and starts the "移動" child
    void sub_71005FE5CC();
    // 0x71005feb18 (declared only, 668 bytes): picks the next roam position (returned in s0 / s1 / s2).
    sead::Vector3f sub_71005FEB18();
    // 0x71005fe85c: changes the height level (random +-1 step, clamped by MexHeightLevel) and starts the "高度変化" child
    void sub_71005FE85C();
    // aitree_variable at offset 0x38
    void* mWizzrobeMagicWeatherUnit_a{};
    // static_param at offset 0x40
    const int* mMoveCountMin_s{};
    // static_param at offset 0x48
    const int* mMoveCountMax_s{};
    // static_param at offset 0x50
    const int* mChangeHeightPer_s{};
    // static_param at offset 0x58
    const int* mMexHeightLevel_s{};
    // static_param at offset 0x60
    const float* mTerritoryRadius_s{};
    // static_param at offset 0x68
    const float* mTerritoryRadiusRnd_s{};
    // static_param at offset 0x70
    const float* mRetryLength_s{};
    // static_param at offset 0x78
    const float* mHeightOffset_s{};
    // dynamic_param at offset 0x80
    sead::Vector3f* mCentralPos_d{};
    u32 _88 = 0;
    u32 _8c = 0;
    u32 _90 = 1;
};
KSYS_CHECK_SIZE_NX150(WizzrobeRoam, 0x98);

}  // namespace uking::ai
