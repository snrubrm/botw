#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <xlink2/xlink2HandleELink.h>
#include <xlink2/xlink2HandleSLink.h>
#include "Game/AI/AI/aiRailMove.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"

namespace uking::ai {

class RemainsFireDroneNormal : public RailMove {
    SEAD_RTTI_OVERRIDE(RemainsFireDroneNormal, RailMove)
public:
    explicit RemainsFireDroneNormal(const InitArg& arg);
    ~RemainsFireDroneNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void m34() override;
    f32 m35() override;
    bool handleMessage_(const ksys::Message& message) override;
    bool handleAck_(const ksys::MessageAck& ack) override;

protected:
    // static_param at offset 0xa0
    const float* mLightLengthOffset_s{};
    // static_param at offset 0xa8
    const bool* mAdjustRadius_s{};
    // map_unit_param at offset 0xb0
    const int* mSearchLightType_m{};
    // map_unit_param at offset 0xb8
    const float* mLightLength_m{};
    // map_unit_param at offset 0xc0
    const float* mLightRadius_m{};
    // aitree_variable at offset 0xc8
    float* mTargetSpeed_a{};
    Unk_710235aba0 _d0{mActor, 0x8000040};
    Unk_710235abc8 _100{mActor, 0x8000006};
    Unk_7102450528 _158;
    Unk_71023f5fc0 _1d0;
    bool _208 = false;
    bool _209 = false;
    bool _20a = false;
    gsys::BoneAccessKeyEx mPropellerTop;
    gsys::BoneAccessKeyEx mPropellerBottom;
    gsys::BoneAccessKeyEx mSearchlight;
    gsys::BoneAccessKeyEx mBody;
    xlink2::HandleELink _2f0;
    xlink2::HandleSLink _300;
    xlink2::HandleSLink _310;
    ksys::act::ModelBindInfo* _320 = nullptr;
    f32 _328 = 5.0f;
    f32 _32c = 30.0f;
    f32 _330 = 0.0f;
    f32 _334 = 0.0f;
    u64 _338 = 0;
};
KSYS_CHECK_SIZE_NX150(RemainsFireDroneNormal, 0x340);

}  // namespace uking::ai
