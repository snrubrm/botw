#pragma once

#include "Game/AI/AI/aiLandHumEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelNormal : public LandHumEnemyNormal {
    SEAD_RTTI_OVERRIDE(LynelNormal, LandHumEnemyNormal)
public:
    explicit LynelNormal(const InitArg& arg);
    ~LynelNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void m37() override;
    void m49(Unk1* out, s32 idx) override;
    void calc_() override;
    bool handleMessage_(const ksys::Message& message) override;

    bool m56(Unk2* out, Unk1* info) override;
    void m57(s32 type, Unk2* target) override;
    void m60(Unk3* out) override;
    bool m63(Unk3* result) override;
protected:
    // aitree_variable at offset 0x400
    int* mLynelAreaAlarmPoint_a{};
    // aitree_variable at offset 0x408
    int* mLynelAIFlags_a{};
    // aitree_variable at offset 0x410
    int* mLynelNoticeAttackRepeatNum_a{};
    Unk_71024056a8 _418;
    s32 _458 = 0;
    bool _45c = false;
};
KSYS_CHECK_SIZE_NX150(LynelNormal, 0x460);

}  // namespace uking::ai
