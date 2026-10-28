#include "Game/Framework/gameSystem.h"
#include "Game/Scene/gameScene.h"
#include "Game/gameSaveSystem.h"
#include "KingSystem/System/Controller.h"
#include "KingSystem/Utils/HeapUtil.h"

// 0x7100f3d204: called after the scene boots; empty in the original.
void nullsub_4162();

// 0x7100923e20: stores the pointer in a write-only global (0x71025d24f8). Only System's
// constructor calls it, with the gyro matrix at SystemStruct1 + 0x38; name is a placeholder.
void sub_7100923E20(sead::Matrix33f* matrix);

namespace uking::frm {

System::System() {
    sub_7100923E20(&mStruct1._38);
}

System::~System() {}

bool System::init(const GameScene::InitArg& arg) {
    mHeap = sead::ExpHeap::create(0, "uking::frm::System", arg.heap, 8,
                                  sead::Heap::cHeapDirection_Forward, true);
    const GameScene::InitArg scene_arg{mHeap, arg.framework};
    mScene = new (mHeap, 8) GameScene;
    if (!mScene->initialize(scene_arg))
        return false;

    nullsub_4162();
    Controller::instance()->__auto0(0, true);
    SystemStruct1::setInstance(&mStruct1);
    ksys::util::adjustHeapOrCurrentHeap(mHeap);
    return true;
}

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
