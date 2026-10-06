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
    void getTargetActorPos(sead::Vector3f* pos) const;
    // 0x71005f4c24: resets flag _1000000, then changes to "予兆" child
    void sub_71005F4C24();
    // 0x71005f4b08: resets flag _1000000, then changes to "意識途切れ" child
    void sub_71005F4B08();
    // 0x71005f49ec: resets flag _1000000, then changes to "落下攻撃" child
    void sub_71005F49EC();
    // 0x71005f4890: resets flag _1000000, then changes to "放物攻撃" child
    void sub_71005F4890();
    // 0x71005f4754: resets flag _1000000, then changes to "攻撃" child
    void sub_71005F4754();
    // 0x71005f4638: sets flag _1000000, then changes to "待機" child at the target actor position
    void sub_71005F4638();
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
