#include "Game/gameStage.h"
#include "Game/Actor/Damage/dmgInfoManager.h"
#include "Game/gameGearMgr.h"
#include "Game/gameGraphics.h"
#include "Game/gameRadarMgr.h"
#include "Game/gameSceneStatusMgr.h"
#include "Game/gameSceneSubsys14.h"
#include "Game/Scene/gameStageInfo.h"
#include "Game/gameSceneSubsysMisc.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/Camera/CameraMgr.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/Terrain/teraSystem.h"
#include "KingSystem/World/worldManager.h"
#include <gsys/gsysResourceEditor.h>

namespace uking {

MainFieldDungeonStage::MainFieldDungeonStage() = default;

void MainFieldDungeonStage::initForStageGen() {
    Graphics::instance()->sub_7100F32AC8(_150, _158);
    ksys::world::sub_71010D6094(ksys::world::Manager::instance()->getEnvMgr());
}

void MainFieldDungeonStage::postInit(Unk_710245ac20* a, Unk_710245abf0* b) {
    Graphics::instance()->getUnk_ab0()->_e48 &= ~2u;
    a->_8 = true;
    if (auto* mgr = GameSceneStatusMgr::instance())
        mgr->unregisterStatus(&mDebugStatus);
    GearMgr::instance()->sub_7100669C88();
    mDebugStatus.clear();
}

void MainFieldDungeonStage::calc() {
    if (ksys::map::PlacementMgr::instance() &&
        !ksys::map::PlacementMgr::instance()->mFlags.isOn(ksys::map::PlacementMgr::MgrFlag::_2)) {
        const auto* camera = ksys::CameraMgr::instance()->getLookAtCamera();
        auto* mgr = ksys::map::PlacementMgr::instance();
        if (camera) {
            if (auto* navi = mgr->mPlacementNavi)
                navi->_34 = camera->getAt() - camera->getPos();
        }
        const sead::Vector3f zero = sead::Vector3f(0, 0, 0);
        if (mgr->isStaticCompoundReady(zero, false) && !_30)
            _30 = true;
    }

    if (auto* mgr = RadarMgr::instance())
        mgr->calc();

    if (auto* mgr = ksys::world::Manager::instance()) {
        const bool in_battle_area = ksys::gdt::getFlag_FinalTrial_InBossBattleArea(false);
        if (mgr->isInFinalTrialBossBattleArea() != in_battle_area) {
            mgr->setInFinalTrialBossBattleArea(in_battle_area);
            mgr->updateGraphicsMap(mgr->getStageType());
        }
    }
    nullsub_2167(GearMgr::instance());
}

void MainFieldDungeonStage::unload() {
    Graphics::instance()->sub_7100F32AC8(nullptr, nullptr);
    auto* terrain = ksys::tera::Terrain::instance();
    if (terrain->isGrassEnabled())
        terrain->sub_710114DE7C(true);
    if (ksys::world::Manager::instance()) {
        ksys::world::Manager::instance()->unload();
        ksys::world::Manager::instance()->unload2();
    }
    callRoot4Stuff();
    if (auto* scene = Graphics::instance()->mModelScenes[0]) {
        scene->mEnv.clearImpl(scene->mEnv.getDataSets(), false);
        scene->clearParticleGroup(-1);
    }
    auto* scene = Graphics::instance()->mModelScenes.unsafeAt(1);
    scene->mEnv.clearImpl(scene->mEnv.getDataSets(), true);
    nullsub_2452(mHeap);
    gsys::ResourceEditor::instance()->sub_7100C5D3E0(nullptr, true);
    ksys::act::BaseProcMgr::instance()->cancelInitializerTasks();
    ksys::phys::HavokAI::instance()->_48->sub_7100F898E4();
    GearMgr::instance()->sub_7100669EE4();
    GearMgr::deleteInstance();
}

void MainFieldDungeonStage::postCalc() {
    sub_71007C33AC();
    act::DamageInfoMgr::instance()->postCalc();
    GameSceneSubsys4::instance()->m6();
    GameSceneSubsys5::instance()->postCalc();
    GameSceneSubsys14::instance()->postCalc();
    GearMgr::instance()->postCalc();
}

void MainFieldDungeonStage::preCalc() {
    ksys::phys::HavokAI::instance()->_48->x(&sead::Vector3f::zero);
    GearMgr::instance()->sub_7100669ED8();
}

MainFieldDungeonStage::~MainFieldDungeonStage() {
    mHeap->destroy();
}

bool MainFieldDungeonStage::m2(sead::BufferedSafeString* out) {
    out->copy(mMapName);
    return true;
}

bool MainFieldDungeonStage::getMapName(sead::BufferedSafeString* out, int x, int z) {
    if (x != 5 || z != 4)
        return false;
    out->copy(mMapName);
    return true;
}

void MainFieldDungeonStage::m4(int* x, int* z, const sead::SafeString& name) {
    *x = 5;
    *z = 4;
}

void MainFieldDungeonStage::getMapType(sead::BufferedSafeString* out) {
    out->copy(uking::StageInfo::getCurrentMapType());
}

int MainFieldDungeonStage::m0() {
    return 2;
}

}  // namespace uking
