#pragma once

#include <math/seadVector.h>
#include "Game/AI/aiUnk_710071edf8.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/GameData/gdtFlagHandle.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::ai {

class HorseNotRidden : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HorseNotRidden, ksys::act::ai::Ai)
public:
    explicit HorseNotRidden(const InitArg& arg);
    ~HorseNotRidden() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    // 0x7100438bc0 (gdt reinit callback; CSV name).
    void setAnimalMasterAppearanceFlagIdx(ksys::gdt::Manager::ReinitEvent* event);

protected:
    // static_param at offset 0x38
    const int* mEscapeCountThreshold_s{};
    // static_param at offset 0x40
    const float* mNearHorseAssociationDistance_s{};
    // static_param at offset 0x48
    const float* mEscapeDelayFramesMin_s{};
    // static_param at offset 0x50
    const float* mEscapeDelayFramesMax_s{};
    // static_param at offset 0x58
    const float* mCallDelayFrames_s{};
    // static_param at offset 0x60
    const float* mAttackFrontDistance_s{};
    // static_param at offset 0x68
    const float* mAttackFrontAngleCos_s{};
    // static_param at offset 0x70
    const float* mAttackBackDistance_s{};
    // static_param at offset 0x78
    const float* mAttackBackAngleCos_s{};
    // static_param at offset 0x80
    const float* mAttackDefinitelyDistance_s{};
    // static_param at offset 0x88
    const float* mAttackIntervalFrames_s{};
    // static_param at offset 0x90
    const float* mMoveAttackCLOSDistanceByRadius_s{};
    // static_param at offset 0x98
    const float* mCarriedItemCosThresholdForEat_s{};
    // static_param at offset 0xa0
    const float* mStaggerVelocityThreshold_s{};
    // static_param at offset 0xa8
    const sead::Vector3f* mCarriedItemPosRTYOffset_s{};
    // static_param at offset 0xb0
    const sead::Vector3f* mCarriedItemPosRTYWidth_s{};
    // dynamic_param at offset 0xb8
    int* mChildSelectAtFirst_d{};
    Unk_710071edf8 _c0{mActor};
    u32 _f0 = 0;
    ksys::act::BaseProcLink _f8;
    u32 _108 = 0;
    sead::Vector3f _10c = sead::Vector3f::zero;
    f32 _118 = 0;
    u32 _11c = 0;
    s32 _120 = -1;
    ksys::gdt::Manager::ReinitSignal::Slot _128{this,
                                                &HorseNotRidden::setAnimalMasterAppearanceFlagIdx};
    ksys::gdt::FlagHandle _198 = ksys::gdt::InvalidHandle;
    sead::Vector3f _19c = sead::Vector3f::zero;
    bool _1a8 = false;
    bool _1a9 = false;
};
KSYS_CHECK_SIZE_NX150(HorseNotRidden, 0x1b0);

}  // namespace uking::ai
