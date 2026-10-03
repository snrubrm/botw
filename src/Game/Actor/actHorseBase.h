#pragma once

#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include <prim/seadSafeString.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "Game/Actor/actExtendedEntity.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class ActorConstDataAccess;
}  // namespace ksys::act

namespace ksys::phys {
class RayCastForRequest;
}  // namespace ksys::phys

namespace uking::act {

class Rideable;

// Placeholder name (vtable 0x71024eb548, 7 slots: empty inline dtor, D0, 5 more; ctor 0x7100e72034,
// size 0x10). HorseBase::_b18; HorseBase::prepareInit_ registers it in the NavMeshCharacter (m45)
// at +0x58.
// TODO: incomplete.
class Unk_71024eb548 {
public:
    // Placeholder (bits of _8; callers convert through the stack like a SEAD_ENUM).
    SEAD_ENUM(Flag, _0, _1, _2)

    Unk_71024eb548();
    virtual ~Unk_71024eb548() = default;

    // FIXME: figure out return types, parameters and names
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();

    /* 0x8 */ sead::BitFlag8 _8;  // = 4 (bit _2)
};
KSYS_CHECK_SIZE_NX150(Unk_71024eb548, 0x10);

// Name from the CSV (HorseBase::*). Base class of Horse. vtable 0x71024eaef8 (149 slots: Actor's
// 148 + m148), RTTI static 0x71025aeeb8 (parent: Actor). ctor 0x7100e64f00 (CSV HorseBase::ctor).
// AI code casts to this class (sead::DynamicCast<HorseBase>, RTTI GOT 0x7102579280).
// TODO: incomplete. Size 0xc58 (Horse's first member is at 0xc58). Members are public: AI code
// reads them directly.
class HorseBase : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(HorseBase, ksys::act::Actor)
public:
    // Placeholder (bits of _a90; callers convert through the stack like a SEAD_ENUM).
    SEAD_ENUM(Flag, _0, _1, _2, _3, _4, _5, _6, _7)

    explicit HorseBase(const CreateArg& arg);
    ~HorseBase() override;

protected:
    void onDeleteRequested_(DeleteReason reason) override;
    void onEnterSleep_() override;
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void onPreDeleteStart_(PrepareArg& arg) override;
    void preDelete2_(const PreDeleteArg& arg) override;
    IsSpecialJobTypeResult isSpecialJobType_(ksys::act::JobType type) override;
    bool canWakeUp_() override;

public:
    Actor* m31() override;
    void m44() override;
    Actor* m48() override;
    void onPreFadeOutDelete() override;
    bool shouldUnload(s32* a1) override;
    void m63() override;
    void initMaybe() override;
    bool m67() override;
    void calcMaybe() override;
    void m70() override;
    void updatePositionMaybe() override;
    bool m81(const ksys::Message& message) override;
    void setMtx(const sead::Matrix34f& mtx, bool a2, bool a3) override;
    s32* getLife() override { return &_b80; }
    void m88() override;
    int getExtraHeapSize() override;
    int m109() override;
    void m114() override;
    void m117(ksys::act::Unk117* arg) override;
    void m118() override;
    Rideable* getHorseOptionsMaybe() override;
    RideableBase* m132() override;
    Unk_7100e8b2b8* getMotorcyclePriorityStuffMaybe() override;
    void m143() override;
    void m144() override { Actor::m144(); }
    bool m146() override;

    // Name from the CSV (Horse's override reads eco StatusEffect ReduceAncientEnemyDamge).
    virtual void loadReduceAncientEnemyDamageInfo() {}

    // CSV name. Reads GParamList HorseUnit (RiddenAnimalType); 1 if there is none.
    s32 x() const;

    // Placeholder names (non-virtual functions called by AI code, the horse manager and Horse).
    bool sub_7100E68270() const;
    s32 sub_7100E68298() const;
    bool sub_7100E696D4() const;
    void sub_7100E6AD3C();
    f32 sub_7100E6AD4C();
    bool sub_7100E6AF2C(ksys::act::BaseProc* proc) const;
    bool sub_7100E6B068(ksys::act::BaseProc* proc) const;
    void sub_7100E6BA08();
    bool sub_7100E6BE40() const;
    f32 sub_7100E6BE6C() const;
    void sub_7100E6BE8C(f32 delta);
    void sub_7100E6BEC0(bool on);
    bool sub_7100E6BF00() const;
    void sub_7100E6BF3C(bool on);
    bool sub_7100E6C094(bool on);
    bool sub_7100E6C0E0(bool on);

    // Zero-initialised as a whole (memset) by the ctor.
    struct Unk1 {
        /* 0x000 */ ksys::act::BaseProcHandle _0;
        /* 0x010 */ ksys::act::BaseProcHandle _10;
        /* 0x020 */ ksys::act::BaseProcHandle _20;
        /* 0x030 */ ksys::act::BaseProcHandle _30;
        /* 0x040 */ sead::FixedSafeString<64> _40;
        /* 0x098 */ sead::FixedSafeString<64> _98;
        /* 0x0f0 */ sead::FixedSafeString<64> _f0;
        /* 0x148 */ sead::FixedSafeString<64> _148;
    };
    KSYS_CHECK_SIZE_NX150(Unk1, 0x1a0);

    /* 0x840 */ ksys::act::BaseProcLink _840;
    /* 0x850 */ ksys::act::BaseProcLink _850;
    /* 0x860 */ ksys::act::BaseProcLink _860;
    /* 0x870 */ ksys::act::BaseProcLink _870;
    /* 0x880 */ ksys::act::BaseProcLink _880;
    /* 0x890 */ sead::CriticalSection _890;
    /* 0x8d0 */ Unk1 _8d0;  // value-initialised by the ctor
    /* 0xa70 */ ksys::phys::RayCastForRequest* _a70 = nullptr;
    /* 0xa78 */ void* _a78 = nullptr;
    /* 0xa80 */ u8 _a80[0xa8c - 0xa80];
    /* 0xa8c */ u32 _a8c = 0;
    /* 0xa90 */ sead::BitFlag8 _a90;
    /* 0xa98 */ ExtendedEntity _a98;
    /* 0xb08 */ void* _b08 = nullptr;
    /* 0xb10 */ Rideable* _b10 = nullptr;  // getHorseOptionsMaybe (RideableHorse, ctor 0x7100e7c688)
    /* 0xb18 */ Unk_71024eb548* _b18 = nullptr;
    /* 0xb20 */ void* _b20 = nullptr;
    /* 0xb28 */ void* _b28 = nullptr;
    /* 0xb30 */ ksys::act::BaseProcLink _b30;
    /* 0xb40 */ void* _b40 = nullptr;
    /* 0xb48 */ void* _b48 = nullptr;
    /* 0xb50 */ ksys::MesTransceiverId _b50;
    /* 0xb68 */ void* _b68 = nullptr;
    /* 0xb70 */ sead::Atomic<u32> _b70 = 0;  // flags (m109)
    /* 0xb74 */ u16 _b74 = 0;  // flags
    /* 0xb78 */ s32 _b78 = -1;
    /* 0xb7c */ s32 _b7c = -1;
    /* 0xb80 */ s32 _b80 = 0;  // getLife
    /* 0xb84 */ f32 _b84 = 0;  // 0..1 (sub_7100E6BE8C)
    /* 0xb88 */ u32 _b88 = 0;
    /* 0xb8c */ u32 _b8c = 0;
    /* 0xb90 */ u32 _b90 = 0;
    /* 0xb94 */ u32 _b94 = 0;
    /* 0xb98 */ u32 _b98 = 0;
    /* 0xb9c */ u32 _b9c = 0;
    /* 0xba0 */ sead::Vector3f _ba0 = sead::Vector3f::ez;
    /* 0xbac */ sead::Vector3f _bac = sead::Vector3f::zero;
    /* 0xbb8 */ f32 _bb8 = 0.02;
    /* 0xbbc */ f32 _bbc = 0;
    /* 0xbc0 */ f32 _bc0 = 0.02;
    /* 0xbc4 */ u32 _bc4 = 0;
    /* 0xbc8 */ u32 _bc8 = 0;
    /* 0xbcc */ u32 _bcc = 0;
    /* 0xbd0 */ u32 _bd0 = 0;
    /* 0xbd4 */ u32 _bd4 = 0;
    /* 0xbd8 */ u32 _bd8 = 0;
    /* 0xbdc */ u32 _bdc = 0;
    /* 0xbe0 */ u32 _be0 = 0;
    /* 0xbe4 */ u32 _be4 = 0;
    /* 0xbe8 */ u32 _be8 = 0;
    /* 0xbec */ u32 _bec = 0;
    /* 0xbf0 */ u32 _bf0 = 0;
    /* 0xbf8 */ void* _bf8 = nullptr;
    /* 0xc00 */ sead::FixedSafeString<48> _c00;
    /* 0xc48 */ u32 _c48 = 0;
    /* 0xc4c */ u32 _c4c = 0;
    /* 0xc50 */ u32 _c50 = 0;
};
KSYS_CHECK_SIZE_NX150(HorseBase, 0xc58);

// 0x7100e6dc50 (declared only): whether the accessor's actor is a HorseBase.
bool sub_7100E6DC50(const ksys::act::ActorConstDataAccess& accessor);

}  // namespace uking::act
