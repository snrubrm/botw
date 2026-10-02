#pragma once

#include "KingSystem/ActorSystem/Awareness/actAITerror.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereRigidBody.h"

namespace uking::behavior {

class TerrorBehavior : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(TerrorBehavior, ksys::act::ai::Behavior)
public:
    explicit TerrorBehavior(const InitArg& arg);
    ~TerrorBehavior() override;
    bool hasUpdateForPreDeleteCb() override { return true; }
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m9() override;
    void loadParams() override;
    bool updateForPreDelete() override { return !_a0._8 || !_a0._8->isAddedToWorld(); }
    void m8() override;

    /* 0x28 */ const int* mLevel_s{};
    /* 0x30 */ const float* mRadius_s{};
    /* 0x38 */ const float* mOffsetSpeedRatio_s{};
    /* 0x40 */ const bool* mIsPlayerLayer_s{};
    /* 0x48 */ const bool* mIsNpcLayer_s{};
    /* 0x50 */ const bool* mIsEnemyLayer_s{};
    /* 0x58 */ const bool* mIsGuardianLayer_s{};
    /* 0x60 */ const bool* mIsImpulseLayer_s{};
    /* 0x68 */ const bool* mIsFireLayer_s{};
    /* 0x70 */ const bool* mIsInsectLayer_s{};
    /* 0x78 */ const bool* mIsHorseLayer_s{};
    /* 0x80 */ const bool* mIsAnimalLayer_s{};
    /* 0x88 */ const bool* mIsWolfLinkLayer_s{};
    /* 0x90 */ const bool* mIsIceLayer_s{};
    /* 0x98 */ const bool* mIsElectricLayer_s{};
    /* 0xa0 */ ksys::act::AITerror _a0{mActor};
};
KSYS_CHECK_SIZE_NX150(TerrorBehavior, 0x158);

}  // namespace uking::behavior
