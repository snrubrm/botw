#include "Game/gameStage.h"
#include "Game/gameGraphics.h"
#include <environment/aglFog.h>
#include <gsys/gsysResourceEditor.h>
#include <gsys/gsysViewer.h>
#include <postfx/aglPfxSky.h>
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/World/worldManager.h"

namespace uking {

ViewerStage::ViewerStage() = default;

ViewerStage::~ViewerStage() {
    mHeap->destroy();
}

void ViewerStage::draw3D(const agl::lyr::RenderInfo& info) {}

void ViewerStage::draw2D(const agl::lyr::RenderInfo& info) {}

s32 ViewerStage::getType() {
    return 5;
}

void ViewerStage::calc() {
    if (ksys::world::Manager::instance()->getStageType() != ksys::StageType::Viewer)
        return;

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

void ViewerStage::unload() {
    if (auto* mgr = ksys::world::Manager::instance())
        mgr->unload();
    callRoot4Stuff();
    if (_20) {
        _20->mEnv.clearImpl(_20->mEnv.getDataSets(), false);
        _20->clearParticleGroup(-1);
    }
    auto* scene = Graphics::instance()->mModelScenes.unsafeAt(1);
    scene->mEnv.clearImpl(scene->mEnv.getDataSets(), true);
    nullsub_2452(mHeap);
    ksys::act::BaseProcMgr::instance()->cancelInitializerTasks();
    gsys::ResourceEditor::instance()->cleanup();
    ksys::VFR::instance()->clearIntervalOverride();
    gsys::Viewer::deleteInstance();
}

void ViewerStage::initForStageGen() {
    ksys::world::sub_71010D6094(ksys::world::Manager::instance()->getEnvMgr());
}

}  // namespace uking
