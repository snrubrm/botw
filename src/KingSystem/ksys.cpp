#include "KingSystem/ksys.h"
#include <heap/seadHeapMgr.h>
#include <thread/seadThread.h>
#include "KingSystem/AOC/aocManager.h"
#include "KingSystem/ActorSystem/actBaseProcCreateTaskSelector.h"
#include "KingSystem/ActorSystem/actBaseProcInitializer.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/ActorSystem/actDebug.h"
#include "KingSystem/System/UIGlue.h"
#include "KingSystem/Quest/qstManager.h"
#include "KingSystem/Utils/Thread/MessageDispatcher.h"
#include "Game/gameGraphics.h"
#include "Game/gameStatisticsMgr.h"
#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/Chemical/chmChemical.h"
#include "KingSystem/Camera/CameraMgr.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/System/KingEditor.h"
#include "KingSystem/System/PlayReportMgr.h"
#include "KingSystem/System/Vibration.h"
#include "KingSystem/Effect/eftEffect.h"
#include "KingSystem/Ecosystem/ecoSystem.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/System/BasicProfiler.h"
#include "KingSystem/System/HavokWorkerMgr.h"
#include "KingSystem/System/StarterPackMgr.h"
#include "KingSystem/System/UI/LayoutResourceMgr.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/Utils/HeapUtil.h"
#include "KingSystem/ActorSystem/LOD/actLODMgr.h"
#include "KingSystem/ActorSystem/Awareness/actAwareness.h"
#include "KingSystem/ActorSystem/actReaction.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/XLink/xlinkManager.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/System/SystemTimers.h"
#include "KingSystem/Terrain/teraSystem.h"
#include <gsys/gsysParticleMgr.h>
#include "Game/gameEventMgr1.h"
#include "Game/gameEventMgrMiniGame.h"
#include "Game/gameNFP.h"

namespace ksys {

// 0x71024f4d40 (file-local, initially true; set by setInitBeforeStageGenDone and initBeforeStageGenA / B).
static bool sInitBeforeStageGenDone = true;

// 0x710260b180 (file-local in the original: addressed with adrp + offset, no GOT entry).
static bool sIsGameOver;

// 0x71024f4d48: the demo name set by setStartingDemoName (loaded through the GOT in the original).
const char* sStartingDemoName;

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

// 0x7100e9cf78 (declared in another TU).
void sub_7100E9CF78(bool value);

// 0x7100f3d1b4: waits for the stage resources and then runs the graphics stage-gen init.
void waitForResourceCreation1() {
    if (auto* placement = map::PlacementMgr::instance())
        placement->_7a8 = -1;
    if (phys::System::instance())
        phys::System::instance()->waitForResourceCreation();
    if (Graphics::instance())
        Graphics::instance()->initBeforeStageGenB();
}

// 0x7100f3d5b0 / 0x7100f3d480 (unnamed in the CSV): the quest step and the event / actor-delete tail
// of the frame.
void sub_7100F3D5B0();
void sub_7100F3D480();

// 0x7100f3d534: the quest, message-dispatch and event steps of the frame.
void CalcQuestAndEventAndActorDeleteOrPreload() {
    if (!act::BaseProcMgr::instance())
        return;
    if (ui::sub_7100EDC580())
        sub_7100F3D5B0();
    if (!act::BaseProcMgr::instance()->isSpecialJobType(act::JobType::PreCalc)) {
        if (qst::Manager::instance())
            qst::Manager::instance()->calc();
        MessageDispatcher::instance()->update();
    }
    sub_7100F3D480();
}

// 0x7100f3d7e4: the world manager's share of the frame calc. While the base proc manager runs a
// special job (pre-calc) the world managers are left alone.
void CalcWorldMgr() {
    if (!act::BaseProcMgr::instance())
        return;

    if (auto* mgr = world::Manager::instance())
        mgr->clearArray();

    if (act::BaseProcMgr::instance()->isSpecialJobType(act::JobType::PreCalc))
        return;

    if (!world::Manager::instance())
        return;
    world::Manager::instance()->calc1(nullptr);
    world::Manager::instance()->calc2(nullptr);
    world::Manager::instance()->calc3(nullptr);
}

// 0x7100f3d864: asks the particle manager to calculate the emitters, runs the base proc manager's calc
// step unless the terrain is loading, and finishes the event manager's frame step.
void CalcParticleAndBaseProcMgr() {
    gsys::ParticleMgr::instance()->getCalcFlags() |= 0x20000;
    gsys::ParticleMgr::instance()->manualCalcEmitter();
    if (tera::sUnk_710260B220._10 != 2)
        act::BaseProcMgr::instance()->calc();
    evt::Manager::instance()->stubbed();
}

// 0x7100f3db0c: once per `_1` request, reports the play statistics, then runs the ecosystem and the
// statistics manager's position update with the player's matrix translation.
void CalcPlayReportAndStatsMgr() {
    if (tera::sUnk_710260B220._1 != 1)
        return;
    if (auto* report = PlayReportMgr::instance())
        report->calc();
    if (auto* ecosystem = eco::Ecosystem::instance())
        ecosystem->calc();
    if (uking::StatisticsMgr::instance()) {
        if (auto* actor_system = act::ActorSystem::instance()) {
            if (auto* link = actor_system->getPlayerLink()) {
                const sead::Vector3f pos = link->getPlayer()->getMtx().getTranslation();
                uking::StatisticsMgr::instance()->updatePosition(&pos);
            }
        }
    }
    tera::sUnk_710260B220._1 = 0;
}

// 0x7100f3f018: runs the attention and vibration managers once per `_2` request.
void CalcAttentionAndVibration() {
    if (tera::sUnk_710260B220._2 != 1)
        return;
    if (auto* attention = act::Attention::instance())
        attention->calc();
    if (auto* vibration = Vibration::instance())
        vibration->calc();
    tera::sUnk_710260B220._2 = 0;
}

// 0x7100f3ed98: hands the placement manager the camera position and the player position. The terrain
// manager's third state replaces the camera position while the terrain is generated.
void CalcPlacementMgr() {
    if (!map::PlacementMgr::instance())
        return;

    sead::Vector3f camera_pos = sead::Vector3f::zero;
    if (auto* camera_mgr = CameraMgr::instance()) {
        if (auto* camera = camera_mgr->getLookAtCamera())
            camera_pos = camera->getPos();
    }

    sead::Vector3f target_pos = sead::Vector3f::zero;
    if (auto* actor_system = act::ActorSystem::instance()) {
        if (auto* link = actor_system->getPlayerLink())
            target_pos = link->getPlayer()->getMtx().getTranslation();
    }

    if (tera::sUnk_710260B220._10 == 4)
        camera_pos = tera::sUnk_710260B220._b8;

    map::PlacementMgr::instance()->preCalc(camera_pos, target_pos, 2, 0x400000);
}

// 0x7100f4193c (placeholder name): runs the physics worker jobs from a non-main thread, then publishes
// the caller's value through `out`.
bool sub_7100F4193C(void* a1, u32 value, u32* out) {
    if (!sead::ThreadMgr::instance()->isMainThread()) {
        phys::System* system = phys::System::instance();
        sead::INamable name("Worker");
        system->runJobsMaybe(&name);
    }
    *out = value;
    return true;
}

// 0x7100f41a54: the placement manager job's entry point.
void callCalcPlacementMgr() {
    CalcPlacementMgr();
}

// NON_MATCHING: the instructions agree; the original places the call block after the return
// (b.eq to the call), ours falls through to it (b.ne over the call).
// 0x7100f41a7c (CSV CalcPlacementMgr2): while the effect manager or the terrain manager is not
// ready, runs the effect manager's placement step.
void CalcPlacementMgr2() {
    if (!eft::Effect::instance() || !tera::sUnk_710260B220._10)
        eft::Effect::instance()->sub_71011B7F60();
}

// 0x7100f419dc: runs the placement manager's calc step.
void sub_7100F419DC() {
    if (auto* mgr = map::PlacementMgr::instance())
        mgr->calc();
}

// 0x7100f41a18: runs the placement manager's stubbed step.
void sub_7100F41A18() {
    if (auto* mgr = map::PlacementMgr::instance())
        mgr->stubbed();
}

// 0x7100f41acc: runs the placement manager's villager update.
void sub_7100F41ACC() {
    if (auto* mgr = map::PlacementMgr::instance())
        mgr->sub_71011E6E8C();
}

// 0x7100f41b08 (placeholder name): the chemical manager's and the world manager's frame steps, in
// the order the original interleaves them.
void sub_7100F41B08() {
    chm::Chemical::instance()->sub_7100D994A0();
    world::Manager::instance()->sub_71010F78C4();
    chm::Chemical::instance()->sub_7100D99520();
    world::Manager::instance()->sub_71010F78E4();
}

// 0x7100f41bac (placeholder name): the placement manager's first step, then the grass core step of
// the terrain's first registered system. An ActorDebug instance without flag 0x100000 skips it.
void sub_7100F41BAC() {
    if (map::PlacementMgr::instance())
        map::PlacementMgr::instance()->sub_71011E9DB0();
    if (act::ActorDebug::instance() &&
        !act::ActorDebug::instance()->hasFlag(act::ActorDebug::Flag::_100000))
        return;
    if (!tera::Terrain::instance())
        return;
    if (!tera::Terrain::instance()->isGrassEnabled() || !tera::sUnk_710260B220.mSystem)
        return;
    auto* grass = tera::Terrain::instance()->sub_710114DE4C();
    auto* system = tera::Terrain::instance()->sub_710114D8D0()->nth(0);
    tera::sub_710114EF3C(grass, system);
}

// 0x7100f41c7c: the world manager's LOD step. A debug instance without flag 0x40000000 skips it.
void sub_7100F41C7C() {
    if (auto* debug = act::ActorDebug::instance()) {
        if (!debug->hasFlag(act::ActorDebug::Flag::_40000000))
            return;
    }
    if (auto* mgr = world::Manager::instance())
        mgr->sub_71010F78A4();
}

// 0x7100f3dbc0: the heap / reaction half of the stage-generation start. `param` is forwarded to the
// reaction actor creation; when `flag` is set the debug logger runs too.
void initBeforeStageGenA(sead::Heap* heap, void* param, bool flag) {
    if (eft::Effect::instance())
        eft::Effect::instance()->initBeforeStageGen(heap);
    if (act::Reaction::instance())
        act::Reaction::instance()->initBeforeStageGen(heap, util::getDebugHeap(),
                                                      act::ActorCreator::instance(), param);

    SystemTimers* timers = SystemTimers::instance();
    if (!timers) {
        SystemTimers::createInstance(heap);
        timers = SystemTimers::instance();
    }
    if (timers)
        timers->init();

    if (phys::System::instance())
        phys::System::instance()->initBeforeStageGen(heap);
    if (flag) {
        Unk_710261f2f8* logger = Unk_710261f2f8::sInstance;
        if (logger)
            logger->debugLog();
    }
    if (Graphics::instance())
        Graphics::instance()->initBeforeStageGenA();
    if (evt::Manager::instance())
        evt::Manager::instance()->initBeforeStageGen();
    sInitBeforeStageGenDone = true;
}

// 0x7100f3dcec: the manager half of the stage-generation start; every subsystem that exists runs its
// initBeforeStageGenB (or the stage-gen init), then the grass state and the stage-gen flag are reset.
void initBeforeStageGenB() {
    if (Graphics::instance())
        Graphics::instance()->initBeforeStageGenB();
    if (map::PlacementMgr::instance())
        map::PlacementMgr::instance()->initBeforeStageGenB();
    if (act::LODMgr::instance())
        act::LODMgr::instance()->initBeforeStageGenB();
    if (EventMgr1::instance())
        EventMgr1::instance()->initBeforeStageGenB();
    if (evt::Manager::instance())
        evt::Manager::instance()->initBeforeStageGenB();
    if (Unk_71024e80e0::instance())
        Unk_71024e80e0::instance()->initBeforeStageGenB();
    if (world::Manager::instance())
        world::Manager::instance()->initBeforeStageGen();
    if (act::Awareness::instance())
        act::Awareness::instance()->initBeforeStageGen();
    if (eft::Effect::instance())
        eft::Effect::instance()->initBeforeStageGenB();
    if (act::Reaction::instance())
        act::Reaction::instance()->initBeforeStageGenB();
    if (snd::SoundMgr::instance())
        snd::SoundMgr::instance()->initBeforeStageGenB();
    if (xlink::Manager::instance())
        xlink::Manager::instance()->initBeforeStageGenB();
    if (VFR::instance())
        VFR::instance()->resetTimeMultipliers();
    if (gdt::Manager::instance())
        gdt::Manager::instance()->onInitBeforeStageGenMaybe();
    if (aoc::Manager::instance())
        aoc::Manager::instance()->setGameDataFlags();
    if (SystemTimers::instance())
        SystemTimers::instance()->init2();
    if (tera::Terrain::instance()->isGrassEnabled()) {
        tera::Terrain::instance()->sub_710114DE4C()->sub_71011509EC();
        tera::Terrain::instance()->sub_710114DE4C()->sub_7101150A70();
    }
    sub_7100E9CF78(true);
    sInitBeforeStageGenDone = true;
}

// 0x7100f3dea0: the subsystem teardown half of the stage unload. Every subsystem that exists is
// reset and released; the UI manager's stage-unload hook runs in the caller (prepareStageUnload).
void prepareStageUnload__() {
    if (Graphics::instance())
        Graphics::instance()->sub_7100F2DDA0();
    if (act::Reaction::instance())
        act::Reaction::instance()->sub_7100EC0D20();
    if (xlink::Manager::instance())
        xlink::Manager::instance()->sub_71012404CC();
    if (SystemTimers::instance()) {
        SystemTimers::instance()->prepareStageUnload();
        SystemTimers::deleteInstance();
    }
    if (phys::System::instance()) {
        res::ResourceMgrTask::instance()->pauseThreads();
        phys::System::instance()->x_0();
        res::ResourceMgrTask::instance()->resumeThreads();
    }
    if (phys::HavokAI::instance())
        phys::HavokAI::instance()->sendStepMessageToNavMeshSysThread(1.0f / 30.0f);
    if (act::ActorDebug::instance())
        act::ActorDebug::instance()->sub_7100D29BD4();
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
        return !ksys::aoc::Manager::instance()->parseVersion();
    }
    return true;
}

void setPlayerLink(act::PlayerLink* link) {
    if (auto* actor_system = act::ActorSystem::instance())
        actor_system->_c0 = link;
    if (auto* attention = act::Attention::instance())
        attention->setPlayerLink(link);
    if (auto* editor = KingEditor::instance())
        editor->mPlayerLink = link;
    if (auto* graphics = Graphics::instance())
        graphics->_360 = link;
    if (auto* effect = eft::Effect::instance())
        effect->_9fb8 = link;
    if (auto* evt_mgr = evt::Manager::instance())
        evt_mgr->_1d108 = link;
    if (auto* report = PlayReportMgr::instance())
        report->mPlayerLink = link;
}

void setStartingDemoName(const char* name) {
    sStartingDemoName = name;
}

void sub_7100F40428(void* camera) {
    if (auto* evt_mgr = evt::Manager::instance())
        evt_mgr->_1d100 = camera;
    if (auto* vibration = Vibration::instance())
        vibration->sub_71010BB85C(camera);
    if (auto* effect = eft::Effect::instance())
        effect->_9fc0 = static_cast<uking::act::Unk_7102459cc0*>(camera);
}

}  // namespace ksys

// 0x7100f3d180: requests the terrain model's unload, stops the amiibo thread and destroys the awareness
// and King editor singletons (stage teardown).
void deleteInstanceForNFPAwarenessAndKingEditor() {
    ksys::tera::sUnk_710260B220._260.requestUnload2();
    NFP::instance()->quitThread();
    ksys::act::Awareness::deleteInstance();
    ksys::KingEditor::deleteInstance();
}
