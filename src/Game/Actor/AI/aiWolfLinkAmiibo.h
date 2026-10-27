#pragma once

#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/Physics/System/physHavokAI.h"

namespace uking::ai {

// Placeholder name (vtable 0x71024ed6a0): the navmesh position query that sub_7100600A6C allocates
// (0x50 bytes) and submits; process() fills the distance pair and the hit position.
class Unk_71024ed6a0 : public ksys::phys::Unk_7102372790 {
public:
    /* 0x34 */ u32 _34 = 1;
    /* 0x38 */ f32 _38 = 0;
    /* 0x3c */ f32 _3c = 0;
    /* 0x40 */ sead::Vector3f _40{0, 0, 0};
    /* 0x4c */ u8 _4c[4];
};
KSYS_CHECK_SIZE_NX150(Unk_71024ed6a0, 0x50);

class WolfLinkAmiibo : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WolfLinkAmiibo, ksys::act::ai::Ai)
public:
    explicit WolfLinkAmiibo(const InitArg& arg);
    ~WolfLinkAmiibo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    // Bits of _5c (names unknown).
    SEAD_ENUM(Flag, _0, _1, _2, _3, _4, _5, _6, _7)
    // inline-only in the original; name is a guess. Evidence: both call sites spill the SEAD_ENUM
    // argument to the stack before the lsl/orr mask.
    void setFlag(Flag flag) { _5c.setDirect(u8((1 << int(flag)) | _5c.getDirect())); }

    void sub_7100600A6C();
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
