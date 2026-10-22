#include "Game/gameSceneSubsys7.h"
#include <heap/seadExpHeap.h>
#include "Game/gameGraphics.h"
#include "Game/gameStageStateMaybe.h"
#include "KingSystem/Terrain/teraSystem.h"

SEAD_SINGLETON_DISPOSER_IMPL(GameSceneSubsys7)

void GameSceneSubsys7::init(sead::Heap* parent) {
    mHeap = sead::ExpHeap::create(0x1900000, "Terrain Scene", parent, sizeof(void*),
                                  sead::Heap::cHeapDirection_Forward, false);
}

void* GameSceneSubsys7::getTeraSystem() const {
    return mTeraSystem;
}

void GameSceneSubsys7::createTeraSystem() {
    gsys::ModelScene* scene = nullptr;
    if (Graphics::instance()->mModelScenes.size() != 0)
        scene = Graphics::instance()->mModelScenes[0];

    if (mTeraSystem)
        return;

    ksys::CreateTeraSystemArg arg;
    arg._10 = nullptr;
    arg._28 = true;
    arg.mHeap = mHeap;
    arg.mModelScene = scene;
    arg.mResourceHandle = &_20;
    arg._8 = nullptr;
    mTeraSystem = CreateTeraSystem(&arg);

    if (uking::StageStateMaybe::sInstance) {
        ksys::tera::Terrain* terrain = ksys::tera::Terrain::instance();
        uking::StageStateMaybe::sInstance->_58[1]->m21(
            terrain ? static_cast<Unk_7102504260*>(terrain) : nullptr, 0);
    }
}
