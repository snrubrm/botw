#pragma once

#include <container/seadBuffer.h>
#include <gsys/gsysModelAccessKey.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <xlink2/xlink2HandleELink.h>
#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

namespace uking::ai {

// Name from the CSV (GuardianAimBeamState::ctor 0x71006f1ea0, init, update, end; destructor
// 0x71006f1f58). Embedded in GuardianAimBeam (+0x68), PriestBossAimBeam and MiniBeamAttack.
// TODO: incomplete (init / update / end not decompiled; member types partly guessed from the
// constructor: four {s32, pointer} pairs are taken to be sead::Buffers).
class GuardianAimBeamState {
public:
    GuardianAimBeamState();
    ~GuardianAimBeamState();

    // 0x71006f1f60. Emits the ELinks named by the first strings ("Target",
    // "Laser", the caller's name, "BeamSightSearch", "BeamSightLocking", "BeamSightLocked").
    // The position of the float parameters relative to the others is a guess.
    bool init(ksys::act::Actor* actor, const sead::SafeString& a1, const sead::SafeString& a2,
              const sead::SafeString& a3, const sead::SafeString& a4, const sead::SafeString& a5,
              const sead::SafeString& a6, f32 a7, f32 a8, f32 a9, f32 a10,
              const sead::Vector3f& target_pos, const sead::SafeString& node_name,
              const sead::Vector3f& node_offset);
    // 0x71006f2240 (declaration only)
    void update(const sead::Vector3f& target_pos);
    // 0x71006f2928 (declaration only)
    void end(const sead::SafeString& elink_name);
    // 0x71006f2d08 (declaration only): fades the emitted ELinks.
    void sub_71006F2D08();

    ksys::act::Actor* _0 = nullptr;
    sead::SafeString _8;
    sead::SafeString _18;
    // Five emitted links (event pointer + create id each): three ELinks and two SLinks.
    xlink2::HandleELink _28;
    xlink2::HandleELink _38;
    xlink2::HandleELink _48;
    xlink2::HandleSLink _58;
    xlink2::HandleSLink _68;
    sead::Vector3f _78 = sead::Vector3f::zero;
    f32 _84 = 0;
    sead::Vector3f _88 = sead::Vector3f::zero;
    f32 _94 = 0;
    f32 _98 = 0;
    f32 _9c = 0;
    gsys::BoneAccessKeyEx _a0;
    f32 _d8 = 0;
    sead::Vector3f _dc = sead::Vector3f::zero;
    sead::Vector3f _e8;
    f32 _f4 = 150.0;
};
KSYS_CHECK_SIZE_NX150(GuardianAimBeamState, 0xf8);

}  // namespace uking::ai
