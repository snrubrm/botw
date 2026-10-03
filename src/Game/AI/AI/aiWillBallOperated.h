#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WillBallOperated : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WillBallOperated, ksys::act::ai::Ai)
public:
    explicit WillBallOperated(const InitArg& arg);
    ~WillBallOperated() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    struct Params {
        // static_param at offset 0x38
        const float* mWarpDist_s{};
        // static_param at offset 0x40
        const float* mAttakedChangeDist_s{};
        // static_param at offset 0x48
        const bool* mIsAttackedTimeAffect_s{};
        // dynamic_param at offset 0x50
        int* mWaitTime_d{};
        // dynamic_param at offset 0x58
        int* mCommand_d{};
        // dynamic_param at offset 0x60
        sead::Vector3f* mBasePos_d{};
        // dynamic_param at offset 0x68
        ksys::act::BaseProcLink* mTargetActor_d{};
    };
    Params mParams;
    f32 _70 = 0;
    Unk_7102450be8 _78;
};
KSYS_CHECK_SIZE_NX150(WillBallOperated, 0x108);

}  // namespace uking::ai
