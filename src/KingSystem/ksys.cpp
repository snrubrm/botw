#include "KingSystem/ksys.h"
#include <heap/seadHeapMgr.h>
#include <thread/seadThread.h>
#include "Game/DLC/aocManager.h"
#include "KingSystem/ActorSystem/actBaseProcCreateTaskSelector.h"
#include "KingSystem/ActorSystem/actBaseProcInitializer.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/ActorSystem/actDebug.h"
#include "KingSystem/System/UIGlue.h"
#include "KingSystem/System/BasicProfiler.h"
#include "KingSystem/System/HavokWorkerMgr.h"
#include "KingSystem/System/StarterPackMgr.h"
#include "KingSystem/System/UI/LayoutResourceMgr.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/World/worldManager.h"

namespace ksys {

// 0x71024f4d40 (file-local, initially true; set by setInitBeforeStageGenDone and initBeforeStageGenA / B).
static bool sInitBeforeStageGenDone = true;

// 0x710260b180 (file-local in the original: addressed with adrp + offset, no GOT entry).
static bool sIsGameOver;

bool isGameOver() {
    return sIsGameOver;
}

void setIsGameOver(bool is_game_over) {
    sIsGameOver = is_game_over;
}

bool sub_7100F3F00C() {
    return sInitBeforeStageGenDone;
}

void sub_7100F3ED50() {
    auto* debug = act::ActorDebug::instance();
    if (debug && !debug->hasFlag(act::ActorDebug::Flag::_200000))
        return;
    if (ui::sUnk_7102606a90Handler)
        ui::sUnk_7102606a90Handler();
}

void sub_7100F3ED80() {
    if (auto* mgr = map::PlacementMgr::instance())
        mgr->sub_71011E6EE0();
}

void sub_7100F3EE94() {
    if (auto* mgr = world::Manager::instance())
        mgr->sub_71010F78A4();
}

}  // namespace ksys

void setInitBeforeStageGenDone(bool done) {
    ksys::sInitBeforeStageGenDone = done;
}

namespace ksys {

void initBaseProcMgr(sead::Heap* heap) {
    sead::ScopedCurrentHeapSetter setter(heap);

    act::BaseProcMgr::createInstance(heap);
    act::BaseProcCreateTaskSelector::createInstance(heap);
    auto* worker_mgr = HavokWorkerMgr::instance();

    act::BaseProcInitializerArgs args{};
    args.queue_size = 1024;
    args.thread_name = "ActorCreate";
    args.task_selector = &act::BaseProcCreateTaskSelector::instance()->getDelegate();
    act::BaseProcMgr::instance()->init(
        heap, u32(act::JobType::Invalid), sead::ThreadMgr::instance()->getMainThread()->getId(),
        worker_mgr->getWorkerThreadId(1), worker_mgr->getWorkerThreadId(2), args);

    act::BaseProcMgr::sConstant0 = u32(act::JobType::PreCalc);
    act::BaseProcMgr::sConstant1 = u32(act::JobType::Calc1);
    act::BaseProcMgr::sConstant2 = u32(act::JobType::Calc2);
    act::BaseProcMgr::sConstant4 = u32(act::JobType::Calc4);
}

void preInitializeApp(const InitParams& params) {
    ksys::BasicProfiler::Scope profiler_scope("ksys::PreInitializeApp");

    // TODO - other parts

    {
        ksys::BasicProfiler::Scope profiler_scope("RequestFontLoad");
        // TODO: FontMgr::createInstance()
        ui::LayoutResourceMgr::createInstance(params.king_sys_heap);
        ui::LayoutResourceMgr::instance()->init(params.king_sys_heap);
        ui::LayoutResourceMgr::instance()->loadLangFont(params.king_sys_heap);
        ui::LayoutResourceMgr::instance()->loadExtraLangFonts(params.king_sys_heap);
    }

    // TODO - other parts
}

// NON_MATCHING: the original negates the parseVersion() result with mvn + and before the shared
// return (we use eor and mask after the merge)
bool checkPreInitializeResourcesStillLoading() {
    if (StarterPackMgr::instance()->bootupGraphicsPackReady() &&
        StarterPackMgr::instance()->bootupPacksReady() &&
        ui::LayoutResourceMgr::instance()->checkLangFontReady() &&
        ui::LayoutResourceMgr::instance()->checkExtraLangFontsReady() &&
        ui::LayoutResourceMgr::instance()->checkVersionReady()) {
        return !uking::aoc::Manager::instance()->parseVersion();
    }
    return true;
}

}  // namespace ksys
