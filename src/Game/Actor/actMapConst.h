#pragma once

#include "KingSystem/ActorSystem/actActor.h"

namespace ksys::act {
class DropData;
}

namespace uking::act {

// Name from the CSV (MapConst::ctor 0x7100e8dde4, MapConst::m*; the namespace is a guess). A map object
// actor (RTTI static 0x71025b7208, vtable 0x71024ec790 (GOT value), size 0x850) that keeps its physics
// at the placement transform. The factory is not identified yet. MapConst::m71 (0x7100e8e010) calls the
// unnamed matrix comparison 0x7100700428 and is not written yet.
class MapConst : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(MapConst, ksys::act::Actor)
public:
    explicit MapConst(const CreateArg& arg);
    ~MapConst() override;

protected:
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;

public:
    void m63() override;
    void initMaybe() override;

    /* 0x83c */ s32 _83c = 0;
    /* 0x840 */ f32 _840 = 0;  // traverse distance of the actor
    /* 0x844 */ bool _844 = true;
    /* 0x845 */ bool _845 = false;
    /* 0x846 */ bool _846 = false;
    /* 0x847 */ u8 _847;
    /* 0x848 */ bool _848 = false;
    /* 0x84c */ u32 _84c = 0;
};
KSYS_CHECK_SIZE_NX150(MapConst, 0x850);

// Shared base of MapConstActive and MergedDungeonParts (CSV name; ctor 0x7100e8e260, RTTI static 0x71025b71f8):
// keeps the static compound instance of the map object in sync with the actor's state.
class MapConstActiveOrMergedDungeonParts : public MapConst {
    SEAD_RTTI_OVERRIDE(MapConstActiveOrMergedDungeonParts, MapConst)
public:
    explicit MapConstActiveOrMergedDungeonParts(const CreateArg& arg);
    ~MapConstActiveOrMergedDungeonParts() override = default;

protected:
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void onDeleteRequested_(DeleteReason reason) override;
    bool canWakeUp_() override;

public:
    void m63() override;
    void initMaybe() override;
};
KSYS_CHECK_SIZE_NX150(MapConstActiveOrMergedDungeonParts, 0x850);

// Factory 0x7100dcfe0 (CSV MapConstActive::construct): new(0x868). RTTI static 0x71025b71e8.
// preDelete2_ (deletes the three members below) and m76 are not written yet.
class MapConstActive : public MapConstActiveOrMergedDungeonParts {
    SEAD_RTTI_OVERRIDE(MapConstActive, MapConstActiveOrMergedDungeonParts)
public:
    explicit MapConstActive(const CreateArg& arg);
    ~MapConstActive() override;

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

protected:
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;

public:
    void m63() override;
    void initMaybe() override;
    ksys::act::Unk_71025ae640* getAtk() override;
    uking::dmg::DamageManagerBase* getDamageMgr() override;
    ksys::act::Unk_71025ae620* getDropData() override;

    // New virtual (vtable slot 148; the secondary vtable offsets of this class are 8 bytes larger than
    // MapConst's): drops / forwards through the drop data.
    virtual void m148();

    /* 0x850 */ ksys::act::Unk_71025ae640* _850 = nullptr;  // ActorAtk
    /* 0x858 */ uking::dmg::DamageManagerBase* _858 = nullptr;
    /* 0x860 */ ksys::act::DropData* _860 = nullptr;
};
KSYS_CHECK_SIZE_NX150(MapConstActive, 0x868);

// Shared base of MapConstPassive (CSV name; ctor 0x7100e8e4a4, RTTI static 0x71025b7228).
class MapConstPassiveBase : public MapConst {
    SEAD_RTTI_OVERRIDE(MapConstPassiveBase, MapConst)
public:
    explicit MapConstPassiveBase(const CreateArg& arg);
    ~MapConstPassiveBase() override = default;

protected:
    void onDeleteRequested_(DeleteReason reason) override;

public:
    void m63() override;
};
KSYS_CHECK_SIZE_NX150(MapConstPassiveBase, 0x850);

// Factory 0x7100dd8e4 (CSV MapConstPassive::construct): new(0x850). RTTI static 0x71025b7218.
class MapConstPassive : public MapConstPassiveBase {
    SEAD_RTTI_OVERRIDE(MapConstPassive, MapConstPassiveBase)
public:
    explicit MapConstPassive(const CreateArg& arg);
    ~MapConstPassive() override;

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);
};
KSYS_CHECK_SIZE_NX150(MapConstPassive, 0x850);

}  // namespace uking::act
