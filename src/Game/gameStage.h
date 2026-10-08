#pragma once

#include <heap/seadHeap.h>
#include <math/seadBoundBox.h>
#include "Game/gameDebugStatus.h"
#include "Game/gameStageBinder.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Event/evtBaseProcLinkForEvent.h"
#include "KingSystem/Map/mapMapProperties.h"
#include "KingSystem/Utils/Thread/MessageTransceiverTxOnly.h"

namespace sead {
class Camera;
}

namespace ksys::world {
class EnvMgr;
// 0x71010d6094 (CSV wm::SkyMgr::initForStageGen; declaration only): called by the stages' initForStageGen with the
// EnvMgr (null while the manager list is shorter than 7 entries).
void sub_71010D6094(EnvMgr* mgr);
}  // namespace ksys::world

namespace uking {

extern bool sIsTitleStageActive;

// OpenWorldStage initialization and both teardown paths maintain the TeraWaterDisable region.
// Other readers use the same XZ bounds and maximum height; storage remains in the original data.
extern sead::BoundBox2f sTeraWaterDisableBounds;
extern f32 sTeraWaterDisableHeight;

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
    /* 0x18 */ sead::Heap* mHeap = nullptr;
    /* 0x20 */ void* _20 = nullptr;
    /* 0x28 */ bool _28 = false;
    /* 0x30 */ void* _30 = nullptr;
    /* 0x38 */ void* _38 = nullptr;
    /* 0x40 */ sead::FixedSafeString<0xff> mMapName;
    /* 0x158 */ bool _158 = false;
    /* 0x159 */ bool _159 = false;
    /* 0x15a */ bool _15a = false;
    /* 0x160 */ void* _160 = nullptr;
    /* 0x168 */ DebugStatus mDebugStatus{"IndoorStage初期化", 2};
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
    /* 0x18 */ sead::Heap* mHeap = nullptr;
    /* 0x20 */ void* _20 = nullptr;
    /* 0x28 */ void* _28 = nullptr;
    /* 0x30 */ bool _30 = false;
    /* 0x38 */ sead::FixedSafeString<0xff> mMapName;
    /* 0x150 */ sead::Camera* _150 = nullptr;  // passed to Graphics::sub_7100F32AC8 by initForStageGen
    /* 0x158 */ void* _158 = nullptr;
    /* 0x160 */ ksys::act::BaseProcLink mLink;
    /* 0x170 */ void* _170 = nullptr;
    /* 0x178 */ DebugStatus mDebugStatus{"MainFieldDungeonStage初期化", 2};
    /* 0x288 */ s32 _288 = 5;
};
static_assert(sizeof(MainFieldDungeonStage) == 0x290);

// Viewer stage (0x150 bytes): Stage + IHandler; two 0x90-byte `GameScene::sb` objects at +0x30 / +0xc0 (an
// ObjArray-like helper with out-of-line ctor / init / dtor) are not modelled; its ctor, destructors, init, preCalc,
// calc and unload are not decompiled.
class ViewerStage : public Stage, public ksys::MessageTransceiverTxOnly::IHandler {
    SEAD_RTTI_OVERRIDE(ViewerStage, Stage)
public:
    ViewerStage();

    // (the first out-of-line virtual: the vtable and the RTTI functions are emitted with it)
    s32 getType() override;
    ~ViewerStage() override;
    bool init(StageArg* arg) override;
    void postInit(Unk_710245ac20* a, Unk_710245abf0* b) override { a->_8 = true; }
    void preCalc() override;
    void calc() override;
    void postCalc() override {}
    void unload() override;
    bool unloadOk() override { return true; }
    void initForStageGen() override;
    void m13() override {}

private:
    /* 0x10 */ sead::Heap* mHeap;
    u8 _18[0x150 - 0x18];
};

}  // namespace uking
