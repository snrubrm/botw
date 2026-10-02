#pragma once

#include "KingSystem/ActorSystem/Awareness/actAITerror.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SpeedTerror : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SpeedTerror, ksys::act::ai::Behavior)
public:
    explicit SpeedTerror(const InitArg& arg);
    ~SpeedTerror() override;
    bool m6(sead::Heap* heap) override;
    void m9() override;
    void loadParams() override;
    void m7() override;  // not decompiled yet (0x7100642d14)
    void m8() override;

    /* 0x28 */ ksys::act::AITerror _28{mActor};
    /* 0xe0 */ const int* mLevel_s{};
    /* 0xe8 */ const float* mRadius_s{};
    /* 0xf0 */ const float* mSpeedTh_s{};
    /* 0xf8 */ const float* mRemoveSpTh_s{};
    /* 0x100 */ const bool* mIsPlayerLayer_s{};
    /* 0x108 */ const bool* mIsNpcLayer_s{};
    /* 0x110 */ const bool* mIsEnemyLayer_s{};
    /* 0x118 */ const bool* mIsGuardianLayer_s{};
    /* 0x120 */ const bool* mIsImpulseLayer_s{};
    /* 0x128 */ const bool* mIsFireLayer_s{};
    /* 0x130 */ const bool* mIsInsectLayer_s{};
    /* 0x138 */ const bool* mIsHorseLayer_s{};
    /* 0x140 */ const bool* mIsAnimalLayer_s{};
    /* 0x148 */ const bool* mIsWolfLinkLayer_s{};
    /* 0x150 */ const bool* mIsIceLayer_s{};
    /* 0x158 */ const bool* mIsElectricLayer_s{};
};
KSYS_CHECK_SIZE_NX150(SpeedTerror, 0x160);

}  // namespace uking::behavior
