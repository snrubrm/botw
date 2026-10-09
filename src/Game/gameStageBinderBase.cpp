#include "Game/gameStageBinder.h"
#include "Game/gameStageFactory.h"
#include "Game/gameUnkRttiClasses.h"

// Native D1 at 0x71007CBC58 directly precedes StageBinder::createStage.
Unk_710245bee0::~Unk_710245bee0() = default;

namespace uking {

StageFactory::StageFactory() = default;
StageFactory::~StageFactory() = default;

StageBinder::StageBinder() : mStage(nullptr) {}

StageBinder::~StageBinder() {
    if (mStage) {
        delete mStage;
        mStage = nullptr;
    }
}

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
