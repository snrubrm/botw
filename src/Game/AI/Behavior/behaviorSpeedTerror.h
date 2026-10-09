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
    void m7() override;
    void m8() override;

    /* 0x28 */ ksys::act::AITerror _28{mActor};
    struct Params {
        const int* mLevel_s{};
        const float* mRadius_s{};
        const float* mSpeedTh_s{};
        const float* mRemoveSpTh_s{};
        const bool* mIsPlayerLayer_s{};
        const bool* mIsNpcLayer_s{};
        const bool* mIsEnemyLayer_s{};
        const bool* mIsGuardianLayer_s{};
        const bool* mIsImpulseLayer_s{};
        const bool* mIsFireLayer_s{};
        const bool* mIsInsectLayer_s{};
        const bool* mIsHorseLayer_s{};
        const bool* mIsAnimalLayer_s{};
        const bool* mIsWolfLinkLayer_s{};
        const bool* mIsIceLayer_s{};
        const bool* mIsElectricLayer_s{};
    };
    /* 0xe0 */ Params mParams;
};
KSYS_CHECK_SIZE_NX150(SpeedTerror, 0x160);

}  // namespace uking::behavior
