#include "Game/SystemPauseMgr.h"
#include <thread/seadThread.h>
#include <time/seadTickSpan.h>
#include "Game/UI/uiOnUiActorMgr.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/euiScreen.h"
#include "Game/gameStruct30.h"
#include "Game/gameRoot38.h"
#include "Game/gameSaveSystem.h"
#include "Game/Scene/gameScene.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/System/PlayReportMgr.h"
#include "KingSystem/GameData/gdtSaveMgr.h"
#include "Game/gameNFP.h"
#include <nn/os.h>

namespace uking {

SystemPauseMgr::SystemPauseMgr() = default;

SystemPauseMgr::~SystemPauseMgr() = default;

void SystemPauseMgr::m2() {
    uking::ui::sub_7100A6D3EC();
}

// 0x710090b5b0
void SystemPauseMgr::openFadeScreen() {
    uking::ui::sub_7100A6D3EC();
    if (auto* mgr = eui::ScreenMgr::instance()) {
        auto* fade = sead::DynamicCast<uking::ui::Fade>(mgr->getScreen(uking::ui::ScreenId::Fade));
        if (fade)
            fade->open(3);
    }
    if (Struct30::instance()->isPanicBloodMoon())
        Root38::instance()->setField2F(true);
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

void SystemPauseMgr::stopNfpAndWaitForSaveMgr() {
    uking::ui::sub_7100A945BC();
    uking::ui::sub_7100A6D3F0();
    if (auto* nfp = NFP::instance()) {
        nfp->quitThread();
        while (nfp->sub_F45BB8())
            sead::Thread::sleep(sead::TickSpan::makeFromMilliSeconds(10));
    }
    nn::os::GetSystemTick();
    if (ksys::SaveMgr::instance()) {
        // The save thread state is re-read through the singleton every iteration.
        while (ksys::SaveMgr::instance()->get38() != 0)
            sead::Thread::sleep(sead::TickSpan::makeFromMilliSeconds(10));
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
