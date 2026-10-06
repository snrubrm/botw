#pragma once

#include <container/seadBuffer.h>
#include <gfx/seadColor.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorBind.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"

namespace gsys {
class Model;
}

namespace ksys::act {
class PlayerArmors;
}

namespace uking::act {

// Placeholder name (vtable 0x71024e8738, ctor 0x7100e4da18, D1 / D0 0x7100e4df2c / 0x7100e4dfd0, TU 0x7100e4da18 -
// 0x7100e4e07c): an ActorBind without its own RTTI that copies the pose of the bound actor and the local
// matrices of the bone pairs found in both models (`mPairs`: bone of the bound actor's model + the bone of
// the own model with the same name). Embedded in ArmorBase at +0x8b0.
class Unk_71024e8738 : public ksys::act::ActorBind {
public:
    struct Pair {
        gsys::BoneAccessKeyEx mKeyA;
        gsys::BoneAccessKeyEx mKeyB;
    };
    static_assert(sizeof(Pair) == 0x70);

    Unk_71024e8738();
    // Inline: ArmorBase's destructor inlines it (the original also has out-of-line copies in its own TU).
    ~Unk_71024e8738() override { sub_7100E4DB7C(); }

    // (m5 is declared first: it is the key function that makes the TU emit the vtable.)
    bool m5(ksys::act::BaseProc* proc) override;
    bool m4(ksys::act::BaseProc* proc) override;

    // 0x7100e4da54: (re)creates `mPairs` with one entry per bone of `model` (placeholder names).
    void sub_7100E4DA54(sead::Heap* heap, gsys::Model* model);
    // 0x7100e4db7c: destroys `mPairs`.
    void sub_7100E4DB7C();

    /* 0x28 */ sead::Buffer<Pair> mPairs;
    /* 0x38 */ s32 mNumPairs = 0;
    /* 0x3c */ u32 mState = 0;
    /* 0x40 */ u8 _40 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_71024e8738, 0x48);

// Names from the CSV (ArmorBase::*, Armor::*; the namespace is a guess; vtables 0x71024e59d8 /
// 0x7102354608, 0x71025ae4e0 is Actor's RTTI). One armor piece (profiles ArmorHead / ArmorUpper / ArmorLower /
// ArmorExtra0-2). Direct child of Actor. Factory: Armor::construct (new(0x9c0)).
class ArmorBase : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(ArmorBase, Actor)
public:
    explicit ArmorBase(const CreateArg& arg);
    ~ArmorBase() override;

    // BaseProc / Actor virtuals overridden by the armor classes.
    InitResult init_() override;
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void onPreDeleteStart_(PrepareArg& arg) override;

    ksys::act::Actor* m31() override;
    void initMaybe() override;
    void calcMaybe() override;
    void m70() override;
    void updatePositionMaybe() override;
    int getCalcTiming() override;
    bool m86() override;
    ksys::act::Chemical* getChemicalStuff() override;

    // The first new virtual (slot 148).
    virtual void m148();

    // 0x7100e2ac20: the actor linked in `_840` (the player / the actor wearing the armor), if it is in the calc
    // state or a player profile ("PauseMenuPlayer" included) and an Actor (placeholder name).
    ksys::act::Actor* getOwner();

    // 0x7100e29b8c: whether one of the gdt flags "Guide_Attack", "Guide_Bow" and "Guide_Shield" is set.
    static bool sub_7100E29B8C();
    // 0x7100e2bacc: sets the material animation frame `_858` (0 - 15) of the armor model (`_860`).
    void sub_7100E2BACC(const s32* frame);
    // 0x7100e29f3c / 0x7100e2a060 / 0x7100e2a3ec (placeholder names): per-profile updates of the armor model
    // (ArmorHead mantle animation, ArmorUpper "Mt_Mant" materials, ArmorExtra0 / 1 attention flag).
    void sub_7100E29F3C();
    void sub_7100E2A060();
    void sub_7100E2A3EC();

    /* 0x840 */ ksys::act::BaseProcLink _840;
    /* 0x850 */ ksys::act::PlayerArmors* _850 = nullptr;
    /* 0x858 */ s32 _858 = -1;
    /* 0x85c */ s32 _85c = -1;
    /* 0x860 */ u8 _860 = 0;
    /* 0x861 */ u8 _861 = 0;
    /* 0x868 */ sead::CriticalSection _868;
    /* 0x8a8 */ u8 _8a8 = 0xff;
    /* 0x8b0 */ Unk_71024e8738 _8b0;
    /* 0x8f8 */ ksys::act::ModelBindInfo _8f8;
    /* 0x998 */ sead::SafeString _998;
};
KSYS_CHECK_SIZE_NX150(ArmorBase, 0x9a8);

// Factory 0x71000012b0: new(0x9c0), the ctor is inlined. Vtable 0x7102354608.
class Armor : public ArmorBase {
    SEAD_RTTI_OVERRIDE(Armor, ArmorBase)
public:
    explicit Armor(const CreateArg& arg);

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

    // (m81 is declared first: it is the key function that makes the TU emit the vtable.)
    bool m81(const ksys::Message& message) override;
    void m148() override;
    // 0x710000131c: true when ActorFlag2 0x200 is set and the Root38 flag 2 is on (same code as DynamicActor's).
    IsSpecialJobTypeResult isSpecialJobType_(ksys::act::JobType type) override;

    /* 0x9a8 */ f32 _9a8 = 0.0f;
    /* 0x9ac */ sead::Color4f _9ac{0.0f, 0.0f, 0.0f, 0.0f};
};
KSYS_CHECK_SIZE_NX150(Armor, 0x9c0);

}  // namespace uking::act

namespace ksys::act::acc {

// Accessor for the armor pieces (functions 0x7100e2bcc4 - 0x7100e2ce80 in the ArmorBase TU; the CSV names them
// act::acc::getArmorEffect*). Each getter reads the value from the actor's GeneralParamList (ArmorBase / Actor with
// a valid param) or, for a dummy param, from the actor info byml (InfoData) by actor name; the Vector3f getters and
// getArmorMaterialAnmFrameMaybe need an ArmorBase. Placeholder class name.
class Armor : public ActorConstDataAccess {
public:
    // 0x7100e2bcc4
    int getArmorDefenceAddLevel() const;
    // 0x7100e2bda8
    const sead::SafeString& getSeriesArmorSeriesType() const;
    // 0x7100e2be58
    bool getSeriesArmorEnableCompBonus() const;
    // 0x7100e2bf44: the head armor's mantle type is above 0.
    bool sub_7100E2BF44() const;
    // 0x7100e2c02c
    int getArmorHeadMantleType() const;
    // 0x7100e2c110
    bool getArmorUpperDisableSelfMantle() const;
    // 0x7100e2c1fc
    int getArmorUpperUseMantleType() const;
    // 0x7100e2c2e0
    const char* getArmorEffectEffectType() const;
    // 0x7100e2c3d8: the effect level when `effect` is this armor's effect type or one of the two effects a combined
    // effect type consists of.
    int getArmorEffectEffectLevel_checkEffect(const sead::SafeString& effect) const;
    // 0x7100e2c844
    bool getArmorEffectAncientPowUp() const;
private:
    int getArmorEffectEffectLevel() const;
public:
    // 0x7100e2c930
    bool getArmorEffectEnableClimbWaterfall() const;
    // 0x7100e2ca1c
    bool getArmorEffectEnableSpinAttack() const;
    // 0x7100e2cb08: the ArmorHead's MaskType (empty without an armor).
    const sead::SafeString& getArmorHeadMaskType() const;
    // 0x7100e2cbb8 / 0x7100e2cd1c: two vectors of the Armor object (zero without an ArmorBase / with a dummy param).
    void sub_7100E2CBB8(sead::Vector3f* out) const;
    void sub_7100E2CD1C(sead::Vector3f* out) const;
    // 0x7100e2ce80: ArmorBase::_858 (-1 without an ArmorBase).
    s32 sub_7100E2CE80() const;
};

}  // namespace ksys::act::acc
