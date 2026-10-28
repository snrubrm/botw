#include "Game/gameStage.h"
#include "Game/E3Mgr.h"
#include "Game/gameGraphics.h"
#include "Game/gamePlayReport.h"
#include "Game/gameRoot4.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/System/StarterPackMgr.h"
#include "KingSystem/Terrain/teraSystem.h"

namespace uking {

TitleStage::TitleStage() : mHeap(nullptr), _18(nullptr), _20(nullptr), _28(nullptr), _30(nullptr) {}

TitleStage::~TitleStage() {
    sIsTitleStageActive = false;
    mHeap->destroy();
}

// 0x71007d461c: stops the title monitoring flag, deletes the title state machine, unloads the title
// pack and both model scenes' environments, and reports the options.
void TitleStage::unload() {
    Root4::instance()->sub_71008BCE5C(Root4::FlagIdx::_0, false, 2);

    if (_28) {
        _28->m6();
        delete _28;
        _28 = nullptr;
    }

    if (ksys::StarterPackMgr::instance())
        ksys::StarterPackMgr::instance()->unloadTitlePack();

    callRoot4Stuff();

    if (_20) {
        _20->mEnv.clearImpl(_20->mEnv.getDataSets(), false);
        _20->clearParticleGroup(-1);
    }

    gsys::ModelScene* scene = Graphics::instance()->mModelScenes.unsafeAt(1);
    scene->mEnv.clearImpl(scene->mEnv.getDataSets(), true);

    nullsub_2452(mHeap);
    ksys::act::BaseProcMgr::instance()->cancelInitializerTasks();

    if (ksys::tera::Terrain::instance()->isGrassEnabled())
        ksys::tera::Terrain::instance()->sub_710114DE7C(true);

    if (E3Mgr::instance() && E3Mgr::instance()->isDemoMode())
        E3Mgr::instance()->set6C(false);

    reportOptionsFromTitleStage();
}

}  // namespace uking
