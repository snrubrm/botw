#pragma once

#include "Game/AI/AI/aiEnemyNormal.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

// Awareness filter used by LandHumEnemyNormal::m56 (vtable 0x7102401238; m2 0x7100463674,
// D0 0x7100463734): flying balloons.
class Unk_7102401238 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;
};

class LandHumEnemyNormal : public EnemyNormal {
    SEAD_RTTI_OVERRIDE(LandHumEnemyNormal, EnemyNormal)
public:
    explicit LandHumEnemyNormal(const InitArg& arg);
    ~LandHumEnemyNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    void m49(Unk1* out, s32 idx) override;
    void m50(Unk1* out, s32 idx) override;

    s32 m52(s32 idx) override;
    s32 m53() override { return 11; }
    bool m56(Unk2* out, Unk1* info) override;
    void m57(s32 type, Unk2* target) override;
    void m58(s32 type, Unk2* target) override;
    void m59() override;
    void m60(Unk3* out) override;
    void m61(Unk3* out) override;
    bool m68(Unk2* out, Unk1* info) override;

    // 0x71004630b0
    void changeToAvoidDanger(Unk2* target);
    // 0x71004631bc
    void changeToFoundFloatingObject(Unk2* target);

protected:
    // static_param at offset 0x3d0
    const float* mTerrorIgnoreDist_s{};
    // static_param at offset 0x3d8
    const float* mExplosivesSearchDist_s{};
    // static_param at offset 0x3e0
    const float* mExplosivesSearchSpeed_s{};
    // static_param at offset 0x3e8
    const float* mExplosivesSearchAng_s{};
    ksys::act::BaseProcLink _3f0;
};
KSYS_CHECK_SIZE_NX150(LandHumEnemyNormal, 0x400);

}  // namespace uking::ai
