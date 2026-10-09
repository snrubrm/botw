#include "Game/gameStageBinder.h"
#include "Game/gameStageFactory.h"

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
