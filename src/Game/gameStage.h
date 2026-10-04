#pragma once

#include <heap/seadHeap.h>
#include "Game/gameStageBinder.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Event/evtBaseProcLinkForEvent.h"
#include "KingSystem/Map/mapMapProperties.h"
#include "KingSystem/Utils/Thread/MessageTransceiverTxOnly.h"

namespace uking {

extern bool sIsTitleStageActive;

// State of the startup save check (0x18 bytes, vtable 0x710245c470: a sead::hostio node).
struct StartupSaveCheckState {
    const void* _0;
    // 0: start loading slot `mSlot`, 1: wait for the load, 2 / 3: done, 4: finished
    s32 mPhase;
    s32 _c;
    s32 mSlot;
};

class StartupSaveCheckStage : public Stage {
    SEAD_RTTI_OVERRIDE(StartupSaveCheckStage, Stage)
public:
    StartupSaveCheckStage();
    ~StartupSaveCheckStage() override;

    s32 getType() override { return 4; }
    bool init(StageArg* arg) override;
    void postInit(Unk_710245ac20* a, Unk_710245abf0* b) override {}
    void preCalc() override {}
    void calc() override;
    void postCalc() override {}
    void unload() override {}
    bool unloadOk() override { return true; }
    void initForStageGen() override {}
    void m13() override {}

private:
    /* 0x08 */ sead::Heap* mHeap;
    /* 0x10 */ StartupSaveCheckState* mState;
};

class TitleStage : public Stage, public ksys::MessageTransceiverTxOnly::IHandler {
    SEAD_RTTI_OVERRIDE(TitleStage, Stage)
public:
    TitleStage();
    ~TitleStage() override;

    s32 getType() override { return 3; }
    bool init(StageArg* arg) override;
    void postInit(Unk_710245ac20* a, Unk_710245abf0* b) override { a->_8 = true; }
    void preCalc() override {}
    void calc() override;
    void postCalc() override {}
    void unload() override;
    bool unloadOk() override { return true; }
    void initForStageGen() override {}
    void m13() override {}

private:
    /* 0x10 */ sead::Heap* mHeap;
    /* 0x18 */ void* _18;
    /* 0x20 */ void* _20;
    /* 0x28 */ void* _28;
    /* 0x30 */ void* _30;
    /* 0x38 */ ksys::evt::BaseProcLinkForEvent _38;
};

// Indoor stage (0x278 bytes). Stage + IHandler + the map properties interface: the overrides of the latter's
// virtuals are also new slots 14-18 of the primary vtable (clang's thunk targets); their order is the
// declaration order below.
class IndoorStage : public Stage,
                    public ksys::MessageTransceiverTxOnly::IHandler,
                    public ksys::map::MapProperties {
    SEAD_RTTI_OVERRIDE(IndoorStage, Stage)
public:
    IndoorStage();
    ~IndoorStage() override;

    s32 getType() override { return 1; }
    bool init(StageArg* arg) override;
    void postInit(Unk_710245ac20* a, Unk_710245abf0* b) override;
    void preCalc() override;
    void calc() override;
    void postCalc() override;
    void unload() override;
    bool unloadOk() override { return true; }
    void initForStageGen() override;
    void m13() override {}

    bool m2(sead::BufferedSafeString* out) override;
    bool getMapName(sead::BufferedSafeString* out, int x, int z) override;
    void m4(int* x, int* z, const sead::SafeString& name) override;
    void getMapType(sead::BufferedSafeString* out) override;
    int m0() override;

private:
    /* 0x18 */ sead::Heap* mHeap;
    /* 0x20 */ void* _20;
    /* 0x28 */ bool _28;
    /* 0x30 */ void* _30;
    /* 0x38 */ void* _38;
    /* 0x40 */ sead::FixedSafeString<0xff> mMapName;
    /* 0x158 */ u8 _158[0x278 - 0x158];
};
static_assert(sizeof(IndoorStage) == 0x278);

class MainFieldDungeonStage : public Stage,
                              public ksys::MessageTransceiverTxOnly::IHandler,
                              public ksys::map::MapProperties {
    SEAD_RTTI_OVERRIDE(MainFieldDungeonStage, Stage)
public:
    MainFieldDungeonStage();
    ~MainFieldDungeonStage() override;

    s32 getType() override { return 2; }
    bool init(StageArg* arg) override;
    void postInit(Unk_710245ac20* a, Unk_710245abf0* b) override;
    void preCalc() override;
    void calc() override;
    void postCalc() override;
    void unload() override;
    bool unloadOk() override { return true; }
    void initForStageGen() override;
    void m13() override {}

    bool m2(sead::BufferedSafeString* out) override;
    bool getMapName(sead::BufferedSafeString* out, int x, int z) override;
    void m4(int* x, int* z, const sead::SafeString& name) override;
    void getMapType(sead::BufferedSafeString* out) override;
    int m0() override;

private:
    /* 0x18 */ sead::Heap* mHeap;
    /* 0x20 */ void* _20;
    /* 0x28 */ void* _28;
    /* 0x30 */ bool _30;
    /* 0x38 */ sead::FixedSafeString<0xff> mMapName;
    /* 0x150 */ u8 _150[0x160 - 0x150];
    /* 0x160 */ ksys::act::BaseProcLink mLink;
    /* 0x170 */ u8 _170[0x290 - 0x170];
};
static_assert(sizeof(MainFieldDungeonStage) == 0x290);

}  // namespace uking
