#include "Game/Framework/gameSystem.h"
#include "Game/Scene/gameScene.h"
#include "Game/gameSaveSystem.h"

// 0x7100923e20: stores the pointer in a write-only global (0x71025d24f8). Only System's
// constructor calls it, with the gyro matrix at SystemStruct1 + 0x38; name is a placeholder.
void sub_7100923E20(sead::Matrix33f* matrix);

namespace uking::frm {

System::System() {
    sub_7100923E20(&mStruct1._38);
}

System::~System() {}

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
