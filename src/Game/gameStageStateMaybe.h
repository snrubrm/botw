#pragma once

#include <basis/seadTypes.h>

namespace uking {

// Placeholder name (lane4 s49, request of lane5): the object behind the pointer at 0x710261ea78 (GOT 0x2590f60), null
// checked by its readers. `_38` is the current stage type (the `Stage::getType()` values: 3 title, 4 startup save
// check, ...), `_58[_38]` the per-type objects (virtual call at slot 20), `_a00` / `_7c0` more flags / data.
// Readers: GameScene::unloadStage, GameScene::handleAppearGameOver, IndoorStage::init, GameSceneSubsys7::createTeraSystem,
// uiManager::initBeforeStageGen, GameTool::m_1 (0xedbbb8), initSomeTerrainStuff (0xf3d314), TerrainCalcCenter::enter_
// (`!sInstance || sInstance->_38 != 1`: the original does `setInitBeforeStageGenDone(false)` and sets bit 0 of its `_40`).
// The writer is not known (no store through the GOT slot or to the address was found). E3Mgr::_auto3 used an undeclared
// `Dummy* test` for it.
class StageStateMaybe {
public:
    static StageStateMaybe* sInstance;  // 0x710261ea78

    u8 _0[0x38];
    /* 0x38 */ s32 _38;
    u8 _3c[0xa00 - 0x3c];
    /* 0xa00 */ u32 _a00;  // bit 6 is set by E3Mgr::_auto3 (in demo mode)
};

}  // namespace uking
