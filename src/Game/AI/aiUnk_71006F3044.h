#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_71000b0800.h"
#include "Game/AI/aiUnk_71023da520.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"


// Placeholder name = constructor address (0x71006f3044; no real name known). Beam helper embedded in
// NeckSpinBeam (+0xb8), BeamosStaticBeam (+0xa8) and ForkGanonBeastBeamShoot (+0x68): spawns the beam
// actor (named by the actions' "BeamActorName" / "BeamActorKey" params) and keeps the BaseProcLink
// to it in the shared "BeamActorLink" AI tree variable (Unk_71023da520). Only the constructor is
// decompiled; the destructor (0x71006f3140, which releases `_80`) and the other methods below are
// declared only.
class Unk_71006f3044 {
public:
    explicit Unk_71006f3044(ksys::act::Actor* actor);
    // 0x71006f3140 (declared only): deletes the beam actor, releases `_80`.
    ~Unk_71006f3044();

    // 0x71006f331c (declared only, 1.4 KB; the init_ of the three Beam actions): spawns the beam actor. `range` is the
    // BeamRange (the map unit value if positive), `muzzle` / `dir` the MuzzleOffset / BeamDirection params.
    void sub_71006F331C(sead::Heap* heap, const sead::SafeString& actor_name, const sead::SafeString& actor_key,
                        const sead::SafeString& bone_name, f32 range, f32 b, const sead::Vector3f* muzzle,
                        const sead::Vector3f* dir, s32 a);
    // 0x71006f3934 (m: the original loads the dummy link's address directly): the link to the beam actor
    // (the shared "BeamActorLink" if it is alive, else the owner's BeamActor parts link).
    ksys::act::BaseProcLink& sub_71006F3934();
    // 0x71006f3a70: moves the beam actor to the owner's position (unless it is already calculating) and
    // registers (true) / unregisters (false) it with the `_88` sender.
    void sub_71006F3A70(bool on);
    // 0x71006f3b84 / 0x71006f38a4 (the second is declared only): act on the beam actor (the second one returns whether the
    // beam is registered).
    void sub_71006F3B84();
    // 0x71006f3bc4: looks up the beam actor via sub_71006F3934 and passes `dir`
    // to it.
    void sub_71006F3BC4(const sead::Vector3f* dir);
    bool sub_71006F38A4(ksys::act::Actor* actor);
    // 0x71006f3a6c: empty.
    void sub_71006F3A6C();
    // 0x71006f3b14: registers (true) / unregisters (false) the beam actor with the `_a0` sender.
    void sub_71006F3B14(bool on);

    /* 0x00 */ u32 _0 = 0;
    /* 0x04 */ u32 _4 = 0;
    /* 0x08 */ ksys::act::Actor* mActor;
    /* 0x10 */ sead::Vector3f _10 = sead::Vector3f::zero;
    /* 0x1c */ sead::Vector3f _1c = sead::Vector3f::ez;
    /* 0x28 */ sead::FixedSafeString<64> _28;
    /* 0x80 */ Unk_71000b0800<Unk_71023da520> _80;
    /* 0x88 */ Unk_710244ffe8 _88;
    /* 0xa0 */ Unk_7102450010 _a0;
    /* 0xb8 */ bool _b8 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_71006f3044, 0xc0);
