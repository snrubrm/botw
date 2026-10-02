#pragma once

#include "Game/AI/AI/aiEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwimEnemyNormal : public EnemyNormal {
    SEAD_RTTI_OVERRIDE(SwimEnemyNormal, EnemyNormal)
public:
    explicit SwimEnemyNormal(const InitArg& arg);
    ~SwimEnemyNormal() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    void sub_71005B488C();
    bool sub_71005B4E0C();

    void m49(Unk1* out, s32 idx) override;
    void m50(Unk1* out, s32 idx) override;
    s32 m52(s32 idx) override;
    s32 m53() override;
    void m60(Unk3* out) override;
    void m61(Unk3* out) override;
    bool m70() override;

protected:
    u8 _3d0 = 0;
};
KSYS_CHECK_SIZE_NX150(SwimEnemyNormal, 0x3d8);

}  // namespace uking::ai
