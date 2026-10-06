#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadDelegate.h>
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include <math/seadBoundSphere.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"

namespace uking::ai {

class GoronHeroDescendentRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GoronHeroDescendentRoot, ksys::act::ai::Ai)
public:
    explicit GoronHeroDescendentRoot(const InitArg& arg);
    ~GoronHeroDescendentRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    // Called through the delegate _240.
    void sub_7100406E90();
    // 0x7100409314 (placeholder name)
    void changeToStopCommand();
    // 0x71004096bc (placeholder name)
    void changeToFollowPlayer();
    // 0x7100409004 (placeholder name): shows the Yunbo pin on the map while the "Fire_Relic_YunboStopGo" flag is set.
    void updateYunboPin();
    // 0x7100409418 (placeholder name): turns towards `_90`'s position (talk / lock-on disabled) with the "ジャンプ準備" child.
    void changeToJumpPrepare();
    // 0x7100409824 (placeholder name)
    void changeToWaitForPlayerApproach();
    // 0x71004090d4 (placeholder name): the current child is one of the cannon jump states.
    bool sub_71004090D4();
    // 0x71004095e4 (placeholder name): the current child is one of the follow / stop states.
    bool sub_71004095E4();
    // 0x71004091ac (placeholder name): the point of the actor's rail (first one) closest to the actor's position;
    // false without rail points
    bool sub_71004091AC(sead::Vector3f* out);
    // 0x7100407988 (placeholder name): sets the message sender's payload link to the actor and, if the actor linked by
    // the "RegistedActorMessageBroadCastTag" link is running, sends it the message (and remembers that in `_200`).
    void sub_7100407988();

protected:
    // static_param at offset 0x38
    const int* mGuardEndDelayTime_s{};
    // static_param at offset 0x40
    const int* mWhistleReactTimeGo_s{};
    // static_param at offset 0x48
    const int* mWhistleReactTimeStop_s{};
    // static_param at offset 0x50
    const int* mAppearWaitTime_s{};
    // static_param at offset 0x58
    const float* mPlayerNearDist_s{};
    // static_param at offset 0x60
    const float* mPlayerLeaveDist_s{};
    // static_param at offset 0x68
    const float* mPlayerSeparateDist_s{};
    // static_param at offset 0x70
    sead::SafeString mFollowModeFlagName_s{};
    // static_param at offset 0x80
    const sead::Vector3f* mPlayerFollowOffset_s{};
    bool _88 = false;
    bool _89 = false;
    bool _8a = false;
    bool _8b = false;
    bool _8c = false;
    sead::Matrix34f _90;
    sead::Matrix34f _c0;
    sead::BoundSphere3f _f0;
    u32 _100 = 0x8000000;
    f32 _104 = 0;
    f32 _108 = 0;
    u32 _10c = 0;
    u64 _110 = 0;
    u32 _118 = 0;
    f32 _11c = -1.0f;
    f32 _120 = -1.0f;
    u32 _124 = 0;
    ksys::MesTransceiverId _128;
    u64 _140 = 0;
    u32 _148 = 0;
    u64 _150 = 0;
    u32 _158 = 0;
    Unk_710235aba0 _160{mActor, 0x8000040};
    Unk_71023f5f90 _190;
    Unk_71023f5fc0 _1c8;
    Unk_71023f5f60 _200;
    sead::Delegate<GoronHeroDescendentRoot> _240{this, &GoronHeroDescendentRoot::sub_7100406E90};
};
KSYS_CHECK_SIZE_NX150(GoronHeroDescendentRoot, 0x260);

// 0x7100a9a6ac (not decompiled; a bool setter on an unknown global, called by the destructor).
void sub_7100A9A6AC(bool on);

}  // namespace uking::ai
