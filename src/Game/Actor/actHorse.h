#pragma once

#include <math/seadBoundBox.h>
#include "Game/AI/aiUnkDamageCallbacks.h"
#include "Game/Actor/actHorseBase.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
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
    /* 0x0f50 */ Actor* _f50 = this;
    /* 0x0f58 */ void* _f58 = nullptr;
    /* 0x0f60 */ u8 _f60[0xfd8 - 0xf60];
    /* 0x0fd8 */ f32 _fd8 = 10.0;
    /* 0x0fdc */ u32 _fdc = 0;
    /* 0x0fe0 */ u32 _fe0 = 0;
    /* 0x0fe4 */ f32 _fe4 = 1.0;
    /* 0x0fe8 */ f32 _fe8 = 10.0;
    /* 0x0fec */ u8 _fec = 0;
    /* 0x0ff0 */ sead::BoundBox3f _ff0;
    /* 0x1008 */ u32 _1008 = 0;
    /* 0x100c */ u32 _100c = 4;
    /* 0x1010 */ s32 _1010 = -1;
    /* 0x1014 */ u32 _1014 = 0;
    /* 0x1018 */ s32 _1018 = -1;
    /* 0x101c */ s32 _101c = -1;
    /* 0x1020 */ u16 _1020 = 0;
    /* 0x1022 */ u8 _1022 = 0;
    /* 0x1028 */ Unk_710244dd20 _1028{this};
    /* 0x1168 */ Unk3 _1168;  // m135
    /* 0x1170 */ Unk_7102451a50 _1170{};
    /* 0x1198 */ u32 _1198 = 0;
    /* 0x11a0 */ void* _11a0 = nullptr;
    /* 0x11a8 */ u8 _11a8 = 0;
    /* 0x11a9 */ s8 _11a9 = 0;  // escape count (NushiEscapeSelector)
};
KSYS_CHECK_SIZE_NX150(Horse, 0x11b0);

}  // namespace uking::act
