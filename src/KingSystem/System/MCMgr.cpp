#include "KingSystem/System/MCMgr.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/Effect/eftEffect.h"
#include "KingSystem/Framework/frmWorkerSupportThreadMgr.h"
#include "KingSystem/Sound/sndMgr.h"

// 0x7100f3ed50 (declared only; 48 B): placeholder name, global namespace.
void sub_710F3ED50();

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(MCMgr)

bool MCMgr::invoked2(void* arg) {
    sub_710F3ED50();
    return true;
}

bool MCMgr::invoked3(void* arg) {
    if (eft::Effect::instance()) {
        eft::Effect::instance()->calcMostProbably();
        if (eft::Effect::instance())
            eft::Effect::instance()->calcMostProbably2();
    }
    return true;
}

bool MCMgr::invoked4(void* arg) {
    if (snd::SoundMgr::instance())
        snd::SoundMgr::instance()->sub_71011FB5AC();
    return true;
}

void MCMgr::processAllBaseProcMgrJobsType3() {
    auto* mgr = act::BaseProcMgr::instance();
    mgr->setEnableExtraJobPush(true);
    do {
        act::BaseProcMgr::instance()->goIdle();
        act::BaseProcMgr::instance()->processExtraJobsDirectly(act::JobType::Calc3, -1, true);
    } while (act::BaseProcMgr::instance()->isPushActorJobType3InsteadOf6());
}

void MCMgr::calc() {
    frm::WorkerSupportThreadMgr::instance()->waitForTask(3);
}

void MCMgr::postCalc() {
    frm::WorkerSupportThreadMgr::instance()->waitForTask(4);
}

void MCMgr::requestInvoker3() {
    frm::WorkerSupportThreadMgr::instance()->submitRequest(4, &mInvoker3);
}

void MCMgr::requestInvoker4OrSound() {
    auto* mgr = frm::WorkerSupportThreadMgr::instance();
    if (mgr->isThreadsPaused()) {
        if (snd::SoundMgr::instance())
            snd::SoundMgr::instance()->sub_71011FB5AC();
    } else {
        mgr->submitRequest(6, &mInvoker4);
    }
}

}  // namespace ksys
