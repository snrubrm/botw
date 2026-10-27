#pragma once

#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include "Game/gameNavMeshSystem.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/Physics/System/physHavokAI.h"

namespace uking::ai {

class WolfLinkAmiibo : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WolfLinkAmiibo, ksys::act::ai::Ai)
public:
    explicit WolfLinkAmiibo(const InitArg& arg);
    ~WolfLinkAmiibo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // Bits of _5c (names unknown).
    SEAD_ENUM(Flag, _0, _1, _2, _3, _4, _5, _6, _7)
    // inline-only in the original; name is a guess. Evidence: both call sites spill the SEAD_ENUM
    // argument to the stack before the lsl/orr mask.
    void setFlag(Flag flag) { _5c.setDirect(u8((1 << int(flag)) | _5c.getDirect())); }
    // inline-only in the original; name is a guess. Evidence: every test spills the SEAD_ENUM argument
    // before the lsl/and mask.
    bool isFlagOn(Flag flag) const { return _5c.isOnBit(int(flag)); }
    void sub_7100600A6C();
    // 0x7100600d28 (CSV placeholder name: AI_AI_WolfLinkAmiibo::checkAndUpdateFlags): updates the
    // spawn flag byte from the current state.
    void checkAndUpdateFlags();
    // 0x71006013d4 (placeholder name): checks the manager singletons and the spawn flags, then either
    // shows an info overlay and fails, warps, or runs sub_7100601594.
    void sub_71006013D4();
    // 0x7100601594 (placeholder name): changes to the display-name-flag child with the spawn flags and
    // the target position.
    void sub_7100601594();
    // 0x7100600bc4 (CSV havokQueryFinished): finishes the navmesh query, casting +-2 m around its hit
    // position to find the ground.
    bool havokQueryFinished();

protected:
    // static_param at offset 0x38
    const int* mAreaSearchCharacterRadius_s{};
    // static_param at offset 0x40
    const float* mAreaThreshold_s{};
    // static_param at offset 0x48
    const float* mAreaSearchRadius_s{};
    sead::Vector3f _50 = sead::Vector3f::zero;
    sead::BitFlag8 _5c;
    // Navigation query (HavokAI::destroyQuery in the destructor).
    Unk_71024ed6a0* _60{};
    bool _68 = false;
};
KSYS_CHECK_SIZE_NX150(WolfLinkAmiibo, 0x70);

}  // namespace uking::ai
