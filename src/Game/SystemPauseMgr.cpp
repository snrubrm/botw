#include "Game/SystemPauseMgr.h"
#include <thread/seadThread.h>
#include <time/seadTickSpan.h>
#include "Game/UI/uiOnUiActorMgr.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameSaveSystem.h"
#include "Game/Scene/gameScene.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/System/PlayReportMgr.h"

namespace uking {

SystemPauseMgr::SystemPauseMgr() = default;

SystemPauseMgr::~SystemPauseMgr() = default;

void SystemPauseMgr::m2() {
    uking::ui::sub_7100A6D3EC();
}

void SystemPauseMgr::waitForOnUiActorMgrAndBlockSaveMaybe() {
    uking::ui::sub_7100A944D8();
    if (uking::ui::OnUiActorMgr::instance()) {
        while (!uking::ui::OnUiActorMgr::instance()->sub_710090AB4C()) {
            uking::ui::OnUiActorMgr::instance()->sub_710090941C();
            sead::Thread::sleep(sead::TickSpan::makeFromMilliSeconds(10));
        }
    }
    if (auto* save = uking::SaveSystem::instance())
        save->_1a50 |= 0x800;
}

void SystemPauseMgr::waitForOnUiActorMgr() {
    uking::ui::sub_7100A944D8();
    if (uking::ui::OnUiActorMgr::instance()) {
        while (!uking::ui::OnUiActorMgr::instance()->sub_710090AB4C()) {
            uking::ui::OnUiActorMgr::instance()->sub_710090941C();
            sead::Thread::sleep(sead::TickSpan::makeFromMilliSeconds(10));
        }
    }
}

void SystemPauseMgr::pauseGameSceneAndWait() {
    uking::sub_71007B7E4C();
    while (!uking::sub_71007B7E6C())
        sead::Thread::sleep(sead::TickSpan::makeFromMilliSeconds(10));
}

void SystemPauseMgr::waitForStageGenFinalStep() {
    uking::gameSceneSetNeedStageGenFinalStepInPreCalc();
    while (!uking::gameSceneIsNotNeedStageGenFinalStepInPreCalc())
        sead::Thread::sleep(sead::TickSpan::makeFromMilliSeconds(10));
}

void SystemPauseMgr::onSystemPauseResume() {
    Unk_71025d1740::instance()->sub_7100901A90(false);
    uking::ui::sub_7100A6D3EC();
    uking::ui::sub_7100A946AC();
    uking::ui::sub_7100A94914(true);
    if (auto* report = ksys::PlayReportMgr::instance())
        report->set30(false);
}

void SystemPauseMgr::clearHideMainLayerAndResumeEvents() {
    uking::ui::sub_7100A944B4();
    Unk_71025d1740::instance()->sub_7100901A90(true);
    ksys::evt::Manager::instance()->_1d1b0 &= ~2u;
}

}  // namespace uking
