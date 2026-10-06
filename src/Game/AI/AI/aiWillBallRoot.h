#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class WillBallRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WillBallRoot, ksys::act::ai::Ai)
public:
    explicit WillBallRoot(const InitArg& arg);
    ~WillBallRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    // 0x71005f5cec: the twin of PriestBossIronBallRoot::m43: starts the "念受信" child for the linked actor _80 (command, base position, wait time)
    void sub_71005F5CEC(s32 command, const sead::Vector3f& base_pos, s32 wait_time);
    // static_param at offset 0x38
    const int* mMagneLightningTime_s{};
    // static_param at offset 0x40
    const int* mMinimizedTime_s{};
    // static_param at offset 0x48
    const float* mImmidiateLightningXZ_s{};
    // static_param at offset 0x50
    const float* mImmidiateLightningY_s{};
    // static_param at offset 0x58
    const float* mImmidiateLightningXZTarget_s{};
    // static_param at offset 0x60
    const float* mImmidiateLightningYTarget_s{};
    // static_param at offset 0x68
    const float* mLightningTimeMinimizeDist_s{};
    // static_param at offset 0x70
    const bool* mIsExplode_s{};
    // map_unit_param at offset 0x78
    const int* mCount_m{};
    ksys::act::BaseProcLink _80;
    Unk_7102450be8 _90;
    Unk_7102450588 _120;
    u32 _170 = 0;
    bool _174 = false;
    bool _175 = false;
    bool _176 = false;
};
KSYS_CHECK_SIZE_NX150(WillBallRoot, 0x178);

}  // namespace uking::ai
