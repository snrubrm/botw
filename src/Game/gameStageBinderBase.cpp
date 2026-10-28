#include "Game/gameStageBinder.h"
#include "Game/gameStageFactory.h"
#include "Game/gameStage.h"
#include "Game/gameOpenWorldStage.h"
#include "Game/gameUnkRttiClasses.h"

namespace uking {

StageFactory::StageFactory() = default;
StageFactory::~StageFactory() = default;

void StageFactory::create(Unk_710245bee0* request) {
    const s32 type = request->mBinder->getType();
    request->mBinder->setHeap(request->mHeap);

    Stage* stage = nullptr;
    switch (type) {
    case 0: {
        auto* binder = static_cast<OpenWorldStageBinder*>(request->mBinder);
        stage = new (request->mHeap, 8) OpenWorldStage;
        stage->init(&binder->_10);
        stage->postInit(&binder->_218, &binder->_210);
        break;
    }
    case 1: {
        auto* binder = static_cast<IndoorStageBinder*>(request->mBinder);
        stage = new (request->mHeap, 8) IndoorStage;
        stage->init(&binder->_10);
        stage->postInit(&binder->_238, &binder->_230);
        break;
    }
    case 2: {
        auto* binder = static_cast<MainFieldDungeonStageBinder*>(request->mBinder);
        stage = new (request->mHeap, 8) MainFieldDungeonStage;
        stage->init(&binder->_10);
        stage->postInit(&binder->_238, &binder->_230);
        break;
    }
    case 3: {
        auto* binder = static_cast<TitleStageBinder*>(request->mBinder);
        stage = new (request->mHeap, 8) TitleStage;
        stage->init(&binder->_10);
        stage->postInit(&binder->_38, &binder->_30);
        break;
    }
    case 4: {
        auto* binder = static_cast<StartupSaveCheckStageBinder*>(request->mBinder);
        stage = new (request->mHeap, 8) StartupSaveCheckStage;
        stage->init(&binder->_10);
        stage->postInit(&binder->_38, &binder->_30);
        break;
    }
    case 5: {
        auto* binder = static_cast<ViewerStageBinder*>(request->mBinder);
        stage = new (request->mHeap, 8) ViewerStage;
        stage->init(&binder->_10);
        stage->postInit(&binder->_38, &binder->_30);
        break;
    }
    }
    *request->mStage = stage;
}

StageBinder::StageBinder() : mStage(nullptr) {}

StageBinder::~StageBinder() {
    if (mStage) {
        delete mStage;
        mStage = nullptr;
    }
}

// NON_MATCHING: the request retains its existing out-of-line destructor, absent from the native caller.
Stage* StageBinder::createStage(Unk_710245a578* arg) {
    Unk_710245bee0 request;
    request._8 = true;
    request.mHeap = arg->mHeap;
    request.mStage = &mStage;
    request.mBinder = this;
    arg->mFactory->create(&request);
    return mStage;
}

void StageBinder::destroyStage() {
    if (mStage) {
        delete mStage;
        mStage = nullptr;
    }
}

Stage* StageBinder::getStage() const {
    return mStage;
}

}  // namespace uking
