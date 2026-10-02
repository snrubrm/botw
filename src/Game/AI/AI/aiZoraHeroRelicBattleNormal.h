#pragma once

#include <container/seadSafeArray.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ZoraHeroRelicBattleNormal : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ZoraHeroRelicBattleNormal, ksys::act::ai::Ai)
public:
    // Position of a linked "DestinationAnchor" map object (filled by sub_710061223C).
    struct Unk1 {
        sead::Vector3f pos{0, 0, 0};
        bool _c = false;
    };
    KSYS_CHECK_SIZE_NX150(Unk1, 0x10);

    explicit ZoraHeroRelicBattleNormal(const InitArg& arg);
    ~ZoraHeroRelicBattleNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void sub_710061223C();
    void sub_7100612434();
    void sub_710061288C();

protected:
    sead::SafeArray<Unk1, 5> _38;
    // static_param at offset 0x88
    const float* mWarpDistanceXZ_s{};
    // static_param at offset 0x90
    const float* mNearPlayerDistanceXZ_s{};
    bool _98 = true;
    s32 _9c = -1;
    sead::Vector3f _a0;
};
KSYS_CHECK_SIZE_NX150(ZoraHeroRelicBattleNormal, 0xb0);

}  // namespace uking::ai
