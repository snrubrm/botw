#pragma once

#include "Game/AI/AI/aiKorokRailMove.h"
#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

class KorokTargetRailMove : public KorokRailMove {
    SEAD_RTTI_OVERRIDE(KorokTargetRailMove, KorokRailMove)
public:
    explicit KorokTargetRailMove(const InitArg& arg);
    ~KorokTargetRailMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // 0x710045e380: turns towards the player (RotSpd) and runs the rail movement once visible.
    void sub_710045E380();
    // 0x710045e4fc: appear / vanish state machine (_e4: 0 appearing, 1 visible, 2 vanished).
    void sub_710045E4FC();

protected:
    // static_param at offset 0xc0
    const float* mRotSpd_s{};
    // map_unit_param at offset 0xc8
    const int* mKorokTargetAppearFrame_m{};
    // map_unit_param at offset 0xd0
    const int* mKorokTargetVanishFrame_m{};
    // map_unit_param at offset 0xd8
    const bool* mIsNoAppearEffect_m{};
    bool _e0 = false;
    s32 _e4 = 2;
    Unk_71012419b4 _e8{};
    bool _108 = false;
    ksys::VFRValue _10c;
    sead::Matrix33f _118;
    bool _13c = false;
    s32 _140 = 0;
    bool _144 = true;
    f32 _148 = -1.0f;
};
KSYS_CHECK_SIZE_NX150(KorokTargetRailMove, 0x150);

}  // namespace uking::ai
