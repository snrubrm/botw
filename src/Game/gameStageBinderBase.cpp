#include "Game/gameStageBinder.h"

namespace uking {

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
