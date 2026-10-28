#include "Game/gameStage.h"
#include "Game/Actor/Damage/dmgInfoManager.h"
#include "Game/Scene/gameStageInfo.h"
#include "Game/gameGearMgr.h"
#include "Game/gameGraphics.h"
#include "Game/gameLastBossMgr.h"
#include "Game/gameRadarMgr.h"
#include "Game/gameSceneStatusMgr.h"
#include "Game/gameSceneSubsys14.h"
#include "Game/gameSceneSubsysMisc.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/ActorSystem/actActorCaptureMgr.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/Camera/CameraMgr.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/Terrain/teraSystem.h"
#include "KingSystem/World/worldManager.h"
#include <environment/aglFog.h>
#include <gsys/gsysResourceEditor.h>
#include <postfx/aglPfxSky.h>

namespace uking {

void IndoorStage::unload() {
    if (ksys::world::Manager::instance()) {
        ksys::world::Manager::instance()->unload();
        ksys::world::Manager::instance()->unload2();
    }
    callRoot4Stuff();
    if (_160) {
        delete _160;
        _160 = nullptr;
    }
    if (auto* scene = Graphics::instance()->mModelScenes[0]) {
        scene->mEnv.clearImpl(scene->mEnv.getDataSets(), false);
        scene->clearParticleGroup(-1);
    }
    if (auto* scene = Graphics::instance()->mModelScenes[1])
        scene->mEnv.clearImpl(scene->mEnv.getDataSets(), true);
    nullsub_2452(mHeap);
    gsys::ResourceEditor::instance()->sub_7100C5D3E0(nullptr, true);
    ksys::act::BaseProcMgr::instance()->cancelInitializerTasks();
    ksys::phys::HavokAI::instance()->_48->sub_7100F898E4();
    if (ksys::tera::Terrain::instance()->isGrassEnabled())
        ksys::tera::Terrain::instance()->sub_710114DE7C(true);
    LastBossMgr::deleteInstance();
    GearMgr::instance()->sub_7100669EE4();
    GearMgr::deleteInstance();
}


void IndoorStage::postInit(Unk_710245ac20* a, Unk_710245abf0* b) {
    a->_8 = true;
    Graphics::instance()->getUnk_ab0()->_e48 |= 2;
    auto* terrain = ksys::tera::Terrain::instance();
    if (terrain->isGrassEnabled())
        terrain->sub_710114DE7C(false);
    if (auto* mgr = GameSceneStatusMgr::instance())
        mgr->unregisterStatus(&mDebugStatus);
    mDebugStatus.clear();
}

void IndoorStage::preCalc() {
    ksys::phys::HavokAI::instance()->_48->x(&sead::Vector3f::zero);
    GearMgr::instance()->sub_7100669ED8();
}

void IndoorStage::calc() {
    if (_160)
        _160->calc();

    if (_158 && ksys::world::Manager::instance()->getStageType() == ksys::StageType::Viewer) {
        agl::pfx::Sky::AdhocFogParam param;

        auto* fog = Graphics::instance()->getFogMaybe();
        Graphics::instance()->getUnk_aa8()->getAdhocFogParam(&param);
        if (fog) {
            param.color = fog->getColor();
            param.near = fog->getStart();
            param.far = fog->getEnd();
        }
        Graphics::instance()->getUnk_aa8()->setAdhocFogParam(param);
    }

    if (ksys::map::PlacementMgr::instance() &&
        !ksys::map::PlacementMgr::instance()->mFlags.isOn(ksys::map::PlacementMgr::MgrFlag::_2)) {
        const auto* camera = ksys::CameraMgr::instance()->getLookAtCamera();
        auto* mgr = ksys::map::PlacementMgr::instance();
        if (camera) {
            if (auto* navi = mgr->mPlacementNavi)
                navi->_34 = camera->getAt() - camera->getPos();
        }
        const sead::Vector3f zero = sead::Vector3f(0, 0, 0);
        if (mgr->isStaticCompoundReady(zero, false) && !_28)
            _28 = true;
    }

    if (auto* mgr = RadarMgr::instance())
        mgr->calc();
    nullsub_2167(GearMgr::instance());
}

void IndoorStage::postCalc() {
    act::DamageInfoMgr::instance()->postCalc();
    GameSceneSubsys4::instance()->m6();
    GameSceneSubsys5::instance()->postCalc();
    LastBossMgr::instance()->postCalc();
    GameSceneSubsys14::instance()->postCalc();
    GearMgr::instance()->postCalc();
}

void IndoorStage::initForStageGen() {
    ksys::world::sub_71010D6094(ksys::world::Manager::instance()->getEnvMgr());
}

IndoorStage::IndoorStage() = default;

IndoorStage::~IndoorStage() {
    mHeap->destroy();
}

bool IndoorStage::m2(sead::BufferedSafeString* out) {
    out->copy(mMapName);
    return true;
}

bool IndoorStage::getMapName(sead::BufferedSafeString* out, int x, int z) {
    if (x != 5 || z != 4)
        return false;
    out->copy(mMapName);
    return true;
}

void IndoorStage::m4(int* x, int* z, const sead::SafeString& name) {
    *x = 5;
    *z = 4;
}

void IndoorStage::getMapType(sead::BufferedSafeString* out) {
    out->copy(uking::StageInfo::getCurrentMapType());
}

int IndoorStage::m0() {
    return 1;
}

}  // namespace uking
