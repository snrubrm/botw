#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadHeap.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace uking {

// Two empty polymorphic helper classes (RTTI base + virtual destructor) that every binder embeds (the Title /
// Viewer binders at 0x30 / 0x38, the OpenWorld one at 0x210 / 0x218). Their out-of-line functions sit in the
// binders' TU (0x71007bee20-0x71007befc4). Names: placeholders after their vtables.
class Unk_710245abf0 {
    SEAD_RTTI_BASE(Unk_710245abf0)
public:
    virtual ~Unk_710245abf0();
};

class Unk_710245ac20 {
    SEAD_RTTI_BASE(Unk_710245ac20)
public:
    virtual ~Unk_710245ac20();

    /* 0x08 */ bool _8;  // set by the stages' postInit
};

// Base of the "arg" classes (RTTI base only; its typeinfo is checked by OpenWorldStageArg's checkDerived...;
// the name is a guess after OpenWorldStageArg). The virtuals are the binder interface of the arg: slots 4 / 5
// return 0 in OpenWorldStageArg.
class StageArg {
    SEAD_RTTI_BASE(StageArg)
public:
    virtual ~StageArg() = default;

    virtual s32 m4() = 0;
    virtual s32 m5() = 0;
    virtual void setHeap(sead::Heap* heap) = 0;
    virtual s32 m7() = 0;
    virtual const sead::SafeString& m8() = 0;
    virtual const sead::SafeString& m9() = 0;
    virtual const sead::SafeString& m10() = 0;
    virtual s32 m11() = 0;
    virtual bool m12() = 0;
};

// A stage (OpenWorldStage, IndoorStage, MainFieldDungeonStage, TitleStage, StartupSaveCheckStage, ViewerStage)
// created from a binder by StageFactory::create (0x71007cbeac), which calls init(binder arg) and then
// postInit(binder helpers). Slot names after the CSV where it has some (init, postInit, preCalc, calc, postCalc,
// unload, unloadOk, initForStageGen); the destructor is trivial (StageBinder's destructor deletes the stage through
// slot 3).
class Stage {
    SEAD_RTTI_BASE(Stage)
public:
    virtual ~Stage() = default;

    virtual s32 getType() = 0;
    virtual bool init(StageArg* arg) = 0;
    virtual void postInit(Unk_710245ac20* a, Unk_710245abf0* b) = 0;
    virtual void preCalc() = 0;
    virtual void calc() = 0;
    virtual void postCalc() = 0;
    virtual void unload() = 0;
    virtual bool unloadOk() = 0;
    virtual void initForStageGen() = 0;
    virtual void m13() = 0;
};

// Describes the stage to create (the type, the map type / name, ...) and owns the created stage. The 13 virtuals
// are implemented by one binder class per stage kind.
// Names: the CSV (IDA) names where there are some (getType, getName); the others are placeholders. m8 / m9 are
// compared against GameScene::getCurrentMapType / getCurrentMapName by initAndReportDungeonLeaveEnter
// (0x71007b79a8).
class StageBinder {
    SEAD_RTTI_BASE(StageBinder)
public:
    // 0x71007cbbbc (abstract: only the C2 constructor exists)
    StageBinder();
    // 0x71007cbbd0 (D1) / 0x71007cbc14 (D0): deletes the stage.
    virtual ~StageBinder();

    // 0 = OpenWorld, 1 = Indoor, 2 = MainFieldDungeon, 3 = Title, 5 = Viewer
    virtual s32 getType() = 0;
    virtual void setHeap(sead::Heap* heap) = 0;
    // -99 = none
    virtual s32 m6() = 0;
    virtual bool m7() = 0;
    virtual const sead::SafeString& m8() = 0;
    virtual const sead::SafeString& m9() = 0;
    virtual const sead::SafeString& m10() = 0;
    virtual s32 m11() = 0;
    virtual bool m12() = 0;

    // 0x71007cbcb8: deletes the stage (if any).
    void destroyStage();
    // 0x71007cbcec
    Stage* getStage() const;

protected:
    /* 0x08 */ Stage* mStage;
};

// The arg of the OpenWorldStageBinder (embedded at 0x10 of the binder).
class OpenWorldStageArg : public StageArg {
    SEAD_RTTI_OVERRIDE(OpenWorldStageArg, StageArg)
public:
    ~OpenWorldStageArg() override;

    s32 m4() override { return 0; }
    s32 m5() override { return 0; }
    void setHeap(sead::Heap* heap) override { mHeap = heap; }
    s32 m7() override { return _1f4; }
    const sead::SafeString& m8() override { return _130; }
    const sead::SafeString& m9() override { return _168; }
    const sead::SafeString& m10() override { return _18; }
    s32 m11() override { return _1f8; }
    bool m12() override { return _1fc; }

    /* 0x008 */ void* _8;
    /* 0x010 */ sead::Heap* mHeap;
    /* 0x018 */ sead::FixedSafeString<0x100> _18;
    /* 0x130 */ sead::FixedSafeString<0x20> _130;
    /* 0x168 */ sead::FixedSafeString<0x20> _168;
    /* 0x1a0 */ sead::FixedSafeString<0x20> _1a0;
    /* 0x1d8 */ bool _1d8;
    u8 _1d9[0x1f4 - 0x1d9];
    /* 0x1f4 */ s32 _1f4;
    /* 0x1f8 */ s32 _1f8;
    /* 0x1fc */ bool _1fc;
};
static_assert(sizeof(OpenWorldStageArg) == 0x200);

// The binders embed an "arg" object at 0x10 (a polymorphic class of the original whose virtuals live in the
// stage's own TU; its fields are declared here directly). The binder virtuals read / write these fields.
// Layout of the Title / Viewer one (0x20 bytes).
struct TitleStageArg {
    // 0x71007d3d40 (returns a global string; ignores `this`)
    const sead::SafeString& getName() const;

    const void* _0;       // vtable of the original
    void* mEnvArchive;    // GameScene::getEnvArchive()
    sead::Heap* mHeap;
    s32 _18;              // -99
    bool _1c;
};

struct ViewerStageArg {
    // 0x71007d4cac / b8 / c4 (declaration only)
    const sead::SafeString& sub_71007D4CAC() const;
    const sead::SafeString& sub_71007D4CB8() const;
    const sead::SafeString& sub_71007D4CC4() const;

    const void* _0;
    void* mEnvArchive;
    sead::Heap* mHeap;
    s32 _18;
};

// Indoor / MainFieldDungeon arg: 0x218 bytes.
struct DungeonStageArg {
    const void* _0;
    void* mEnvArchive;
    sead::Heap* mHeap;
    sead::FixedSafeString<0x20> _18;
    sead::FixedSafeString<0x20> _50;
    sead::FixedSafeString<0x20> _88;
    u8 _c0[0x210 - 0xc0];
    s32 _210;
    s32 _214;
    bool _218;
};

struct StartupSaveCheckStageArg {
    // 0x71007d17d8 (out of line; empty)
    ~StartupSaveCheckStageArg();
    // 0x71007d17e0 ... 0x71007d182c (declaration only)
    s32 sub_71007D17E0();
    void sub_71007D17F0(sead::Heap* heap);
    s32 sub_71007D17F8();
    const sead::SafeString& sub_71007D1800();
    const sead::SafeString& sub_71007D180C();
    const sead::SafeString& sub_71007D1818();
    s32 sub_71007D1824();
    bool sub_71007D182C();

    const void* _0;
};

class TitleStageBinder : public StageBinder {
    SEAD_RTTI_OVERRIDE(TitleStageBinder, StageBinder)
public:
    ~TitleStageBinder() override;

    s32 getType() override { return 3; }
    void setHeap(sead::Heap* heap) override { _10.mHeap = heap; }
    s32 m6() override { return _10._18; }
    bool m7() override { return m6() != -99; }
    const sead::SafeString& m8() override { return _10.getName(); }
    const sead::SafeString& m9() override { return sead::SafeString::cEmptyString; }
    const sead::SafeString& m10() override { return sead::SafeString::cEmptyString; }
    s32 m11() override { return -1; }
    bool m12() override { return _10._1c; }

private:
    /* 0x10 */ TitleStageArg _10;
    /* 0x30 */ Unk_710245abf0 _30;
    /* 0x38 */ Unk_710245ac20 _38;
};

class ViewerStageBinder : public StageBinder {
    SEAD_RTTI_OVERRIDE(ViewerStageBinder, StageBinder)
public:
    ~ViewerStageBinder() override;

    s32 getType() override { return 5; }
    void setHeap(sead::Heap* heap) override { _10.mHeap = heap; }
    s32 m6() override { return _10._18; }
    bool m7() override { return m6() != -99; }
    const sead::SafeString& m8() override { return _10.sub_71007D4CAC(); }
    const sead::SafeString& m9() override { return _10.sub_71007D4CB8(); }
    const sead::SafeString& m10() override { return _10.sub_71007D4CC4(); }
    s32 m11() override { return -1; }
    bool m12() override { return true; }

private:
    /* 0x10 */ ViewerStageArg _10;
    /* 0x30 */ Unk_710245abf0 _30;
    /* 0x38 */ Unk_710245ac20 _38;
};

class OpenWorldStageBinder : public StageBinder {
    SEAD_RTTI_OVERRIDE(OpenWorldStageBinder, StageBinder)
public:
    ~OpenWorldStageBinder() override;

    s32 getType() override { return 0; }
    void setHeap(sead::Heap* heap) override { _10.mHeap = heap; }
    s32 m6() override { return _10._1f4; }
    bool m7() override { return m6() != -99; }
    const sead::SafeString& m8() override { return _10._130; }
    const sead::SafeString& m9() override { return _10._168; }
    const sead::SafeString& m10() override { return _10._18; }
    s32 m11() override { return _10._1f8; }
    bool m12() override { return _10._1fc; }

private:
    /* 0x010 */ OpenWorldStageArg _10;
    /* 0x210 */ Unk_710245abf0 _210;
    /* 0x218 */ Unk_710245ac20 _218;
};
static_assert(sizeof(OpenWorldStageBinder) == 0x228);

class IndoorStageBinder : public StageBinder {
    SEAD_RTTI_OVERRIDE(IndoorStageBinder, StageBinder)
public:
    ~IndoorStageBinder() override;

    s32 getType() override { return 1; }
    void setHeap(sead::Heap* heap) override { _10.mHeap = heap; }
    s32 m6() override { return _10._210; }
    bool m7() override { return m6() != -99; }
    const sead::SafeString& m8() override { return _10._18; }
    const sead::SafeString& m9() override { return _10._50; }
    const sead::SafeString& m10() override { return _10._88; }
    s32 m11() override { return _10._214; }
    bool m12() override { return _10._218; }

private:
    /* 0x10 */ DungeonStageArg _10;
};

class MainFieldDungeonStageBinder : public StageBinder {
    SEAD_RTTI_OVERRIDE(MainFieldDungeonStageBinder, StageBinder)
public:
    ~MainFieldDungeonStageBinder() override;

    s32 getType() override { return 2; }
    void setHeap(sead::Heap* heap) override { _10.mHeap = heap; }
    s32 m6() override { return _10._210; }
    bool m7() override { return m6() != -99; }
    const sead::SafeString& m8() override { return _10._18; }
    const sead::SafeString& m9() override { return _10._50; }
    const sead::SafeString& m10() override { return _10._88; }
    s32 m11() override { return _10._214; }
    bool m12() override { return _10._218; }

private:
    /* 0x10 */ DungeonStageArg _10;
};

class StartupSaveCheckStageBinder : public StageBinder {
    SEAD_RTTI_OVERRIDE(StartupSaveCheckStageBinder, StageBinder)
public:
    ~StartupSaveCheckStageBinder() override;

    s32 getType() override { return _10.sub_71007D17E0(); }
    void setHeap(sead::Heap* heap) override { _10.sub_71007D17F0(heap); }
    s32 m6() override { return _10.sub_71007D17F8(); }
    bool m7() override { return m6() != -99; }
    const sead::SafeString& m8() override { return _10.sub_71007D1800(); }
    const sead::SafeString& m9() override { return _10.sub_71007D180C(); }
    const sead::SafeString& m10() override { return _10.sub_71007D1818(); }
    s32 m11() override { return _10.sub_71007D1824(); }
    bool m12() override { return _10.sub_71007D182C(); }

private:
    /* 0x10 */ StartupSaveCheckStageArg _10;
};

}  // namespace uking
