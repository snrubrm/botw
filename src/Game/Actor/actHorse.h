#pragma once

#include <math/seadBoundBox.h>
#include "Game/AI/aiUnkDamageCallbacks.h"
#include "Game/Actor/actHorseBase.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"
#include "KingSystem/ActorSystem/actUnk_7102459df8.h"

namespace uking::act {

// Name from the CSV (Horse::*). vtable 0x7102361f50 (150 slots: HorseBase's 149 + m149),
// RTTI static 0x71025afd08 (parent: HorseBase). Factory 0x7100080604 (CSV Horse::construct, which
// inlines the ctor): new(0x11b0).
// TODO: incomplete. Members are public: AI code reads them directly.
class Horse : public HorseBase {
    SEAD_RTTI_OVERRIDE(Horse, HorseBase)
public:
    explicit Horse(const CreateArg& arg);
    ~Horse() override;

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

protected:
    void onEnterSleep_() override;
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void onPreDeleteStart_(PrepareArg& arg) override;
    void preDelete2_(const PreDeleteArg& arg) override;

public:
    bool m50() override;
    bool m55() override { return true; }
    void initMaybe() override;
    void calcMaybe() override;
    void m73() override;
    void m76(ksys::VFR::ScopedDeltaSetter* setter) override;
    bool m81(const ksys::Message& message) override;
    void m96(s32* a1, s32* a2) override {
        *a1 = _d20.getField50();
        *a2 = _d20.getDamage();
    }
    ksys::act::Unk_71025ae640* getAtk() override { return &_c58; }
    ksys::act::Unk_71025b08f8* m126() override { return &_cd8; }
    dmg::DamageManagerBase* getDamageMgr() override { return &_d20; }
    Unk3* m135() override { return &_1168; }
    void loadReduceAncientEnemyDamageInfo() override;

    // FIXME: figure out return types, parameters and names
    virtual void m149();

    /* 0x0c58 */ ksys::act::ActorAtk _c58{this};  // getAtk
    /* 0x0cd8 */ ksys::act::Unk_7102459df8 _cd8{this};  // m126
    /* 0x0d20 */ dmg::DamageManager _d20{this};  // getDamageMgr
    /* 0x0f50 */ ksys::act::Unk_71006ecc78 _f50{this};  // ragdoll controller (embedded; same inlined ctor as DynamicActor::initField868)
    /* 0x1028 */ Unk_710244dd20 _1028{this};
    /* 0x1168 */ Unk3 _1168;  // m135
    /* 0x1170 */ Unk_7102451a50 _1170{};
    /* 0x1198 */ u32 _1198 = 0;
    /* 0x11a0 */ void* _11a0 = nullptr;
    // Placeholder (bits of _11a8; callers convert through the stack like a SEAD_ENUM).
    SEAD_ENUM(Flag, _0)
    /* 0x11a8 */ sead::BitFlag8 _11a8;  // bit 0: _1170 is registered as a damage callback
    /* 0x11a9 */ s8 _11a9 = 0;  // escape count (NushiEscapeSelector)
};
KSYS_CHECK_SIZE_NX150(Horse, 0x11b0);

}  // namespace uking::act
