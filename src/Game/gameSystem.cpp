#include "Game/Framework/gameSystem.h"
#include "Game/Scene/gameScene.h"
#include "Game/gameSaveSystem.h"

namespace uking::frm {

bool System::isReady() {
    if (mScene)
        return mScene->areResourcesReadyMaybe();
    return true;
}

void System::finalizeBootup() {
    if (mScene)
        loadBootupResources(mScene);
}

void System::preCalc(sead::Framework* const& framework) {
    const sead::Framework* fw = framework;
    mScene->preCalc(fw);
}

void System::calcAndRunStateMachine(sead::Framework* const& framework) {
    mStruct1.calcController();
    SaveSystem::instance()->calc();
    const sead::Framework* fw = framework;
    mScene->calcAndRunStateMachine(fw);
}

void System::postCalc(sead::Framework* const& framework) {
    const sead::Framework* fw = framework;
    mScene->postCalc(fw);
}

}  // namespace uking::frm
