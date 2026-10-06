#include "Game/gameSceneSubsys13.h"
#include "Game/UI/uiUnkSingletons.h"
#include "KingSystem/System/PlayReportMgr.h"

SEAD_SINGLETON_DISPOSER_IMPL(GameSceneSubsys13)

GameSceneSubsys13::~GameSceneSubsys13() = default;

void GameSceneSubsys13::init() {
    _34 = -1;
    _38 = 0;
}

void GameSceneSubsys13::sub_71008A53E4() {
    _34 = -1;
    _38 = 0;
}

// NON_MATCHING: `_34 < 0 ? _34 + 1 : 0` becomes add + and-with-sign-mask instead of cmp + csinc.
void GameSceneSubsys13::setGameOverPosition(sead::Vector3f pos) {
    _34 = _34 < 0 ? _34 + 1 : 0;
    if (_38 < 1)
        ++_38;
    _28 = pos;
    uking::ui::UiSubsys1::instance()->sub_7100961E48(&pos);
    if (auto* mgr = ksys::PlayReportMgr::instance())
        mgr->setPlayerTrackReporter30();
}
