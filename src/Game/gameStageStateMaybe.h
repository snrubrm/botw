#pragma once

#include <basis/seadTypes.h>

class Unk_71024f13f0;

namespace uking {

// The object for one stage type at StageStateMaybe::_58[type]. Only its slot 24 (offset 0xc0), which returns the
// stage's active navi tool, is known; the other slots are placeholders for the vtable positions.
class StageStateMaybeObject {
public:
    virtual ~StageStateMaybeObject();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual Unk_71024f13f0* m24();
};

// Placeholder name (lane4 s49, request of lane5): the object behind the pointer at 0x710261ea78 (GOT 0x2590f60), null
// checked by its readers. `_38` is the current stage type (the `Stage::getType()` values: 3 title, 4 startup save
// check, ...), `_58[_38]` the per-type objects (virtual calls at slots 20 / 24), `_a00` / `_7c0` more flags / data.
// Readers: GameScene::unloadStage, GameScene::handleAppearGameOver, IndoorStage::init, GameSceneSubsys7::createTeraSystem,
// uiManager::initBeforeStageGen, GameTool::m_1 (0xedbbb8), initSomeTerrainStuff (0xf3d314), TerrainCalcCenter::enter_
// (`!sInstance || sInstance->_38 != 1`: the original does `setInitBeforeStageGenDone(false)` and sets bit 0 of its `_40`).
// The writer is not known (no store through the GOT slot or to the address was found). E3Mgr::_auto3 used an undeclared
// `Dummy* test` for it.
class StageStateMaybe {
public:
    static StageStateMaybe* sInstance;  // 0x710261ea78

    // 0x710122dc60: whether `tool` is the active navi tool of the object for the current stage type.
    static bool isActiveNaviMaybe(const Unk_71024f13f0* tool);

    u8 _0[0x38];
    /* 0x38 */ s32 _38;
    u8 _3c[0x58 - 0x3c];
    /* 0x58 */ StageStateMaybeObject* _58[6];
    u8 _88[0xa00 - 0x88];
    /* 0xa00 */ u32 _a00;  // bit 6 is set by E3Mgr::_auto3 (in demo mode)
};

}  // namespace uking
