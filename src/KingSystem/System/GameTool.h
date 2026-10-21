#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <nn/os.h>
#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/System/SeadController.h"
#include "KingSystem/Utils/Types.h"

// Base of the debug tools with a hostio name (GameTool, PlacementNavi, the terrain editor), vtable 0x71024f13f0.
// Its RTTI functions (0x7100edc138 / 0x7100edc1a8) are shared by GameTool and PlacementNavi.
class Unk_71024f13f0 {
    SEAD_RTTI_BASE(Unk_71024f13f0)
public:
    Unk_71024f13f0() = default;
    // The tools point _28 at their SeadController during construction.
    explicit Unk_71024f13f0(ksys::SeadController* controller) : _28(controller) {}
    // 0x7100edc270. The original keeps the vtable store that a defaulted destructor drops; written like
    // upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229). Inlined into the
    // PlacementNavi destructor.
    virtual ~Unk_71024f13f0() { ; }
    virtual const char* getName() const = 0;
    virtual const char* getJpName() const = 0;
    // 0x7100edc288; the first out-of-line virtual, so GameTool.cpp emits the vtable.
    virtual void m6();
    virtual bool m7() { return false; }
    // 0x7100edc21c: calls 0x710109c920 twice (arg 1, arg 3) and (arg 2, arg 3); types unknown.
    virtual void m8();
    virtual bool m9() { return true; }
    virtual void m10() {}
    virtual void m11() {}
    virtual void m12() {}
    virtual void m13() {}
    virtual void m14() {}
    virtual void m15() {}
    virtual void m16() {}

    u64 _8 = 0;
    u64 _10 = 0;
    u64 _18 = 0;
    u64 _20 = 0;
    void* _28 = nullptr;
    u32 _30 = 5;
};

namespace ksys {

// vtable 0x71024f1358. Native factory 0x7100EDB87C allocates 0x260 bytes.
// GameScene::StageMgrRun reads _54 bit 0; unloadStage clears that bit.
class GameTool : public Unk_71024f13f0 {
    GameTool();
    ~GameTool() override;

public:
    const char* getName() const override { return "GameTool"; }
    const char* getJpName() const override { return "ゲームツールです"; }
    void m6() override;
    bool m7() override;
    void m14() override;
    void m16() override {}

    SEAD_SINGLETON_DISPOSER(GameTool)

public:
    sead::BitFlag8 _54;
    SeadController mController{0xc};
    nn::os::Tick mTick = nn::os::GetSystemTick();
    f32 _250 = 0;
    u8 _254 = 0;
    u8 _255 = 0;
    u8 _256 = 0;
    u8 _257 = 0;
    u8 _258 = 1;
    u8 _259 = 0;
    s32 _25c = 0;
};
KSYS_CHECK_SIZE_NX150(GameTool, 0x260);

}  // namespace ksys
