#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <xlink2/xlink2HandleELink.h>
#include <xlink2/xlink2HandleSLink.h>
#include "Game/Actor/AI/aiRailMove.h"
#include "Game/Actor/aiUnk_7102357210.h"
#include "Game/Actor/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"

namespace uking::ai {

class RemainsFireDroneNormal;

// Native init 541C84 allocates 0xa8 bytes, constructs ModelBindInfo and stores the owner at 0xa0.
// Table 24192E0 inherits the ModelBindInfo RTTI and all slots except m5 and the deleting destructor.
class Unk_71024192e0 : public ksys::act::ModelBindInfo {
public:
    explicit Unk_71024192e0(RemainsFireDroneNormal* owner) : mOwner(owner) {}
    bool m5(ksys::act::BaseProc* proc) override;

    /* 0xa0 */ RemainsFireDroneNormal* mOwner;
};
KSYS_CHECK_SIZE_NX150(Unk_71024192e0, 0xa8);

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
    bool handleMessage_(const ksys::Message* message) override;
    bool handleAck_(const ksys::MessageAck* ack) override;

    // Unnamed in the binary (0x71005420f4): changes to the "停止" child with the home position as stop target.
    void stopAtHomeMaybe();
    // Unnamed in the binary (0x71005421fc): records this actor in the sender's payload and sends its message
    // to the actor linked by the "RegistedActorMessageBroadCastTag" link.
    void broadcastToLinkedActorMaybe();
    // Complete 1740-byte bind callback 543C18 uses the bound Actor and returns success.
    bool sub_7100543C18(ksys::act::Actor* actor);

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
