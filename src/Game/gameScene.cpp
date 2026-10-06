#include "Game/gameScene.h"
#include "Game/gameSceneStateMachine.h"
#include "KingSystem/System/StageInfo.h"

namespace uking {

// Internal-linkage globals of the GameScene TU (0x728 / 0x72c / 0x730; the original addresses them
// directly, not through the GOT).
static bool sSceneStartEventReady;
static bool sIsTransitionFromFarActorDone;
static bool sIsStageUnloaded;

bool GameScene::sIsOpenWorldDemo{};
GameScene* GameScene::sInstance;
bool GameScene::sIsInitialisingStage;
GameScene* GameScene::sInstance2;
GameScene* GameScene::sInstance3;
bool GameScene::sFlag;

const ksys::StateBase& StateMachineOwnerBinding::getState() const {
    return *mState;
}

void StateMachineOwnerBinding::enter() {
    mRunCount = 0;
    mState->enter(mOwner);
}

void StateMachineOwnerBinding::run() {
    mState->run(mOwner);
    ++mRunCount;
}

void StateMachineOwnerBinding::leave() {
    mState->leave(mOwner);
    mState = nullptr;
    mRunCount = 0;
}

ksys::StateMachine::Unk2* StateMachineOwnerBindingHolder::setState(const ksys::StateBase* state) {
    mBinding.mState = state;
    return &mBinding;
}

// NON_MATCHING: only instruction scheduling of the final tail call differs (the original puts `add x1` after the frame
// restore). D0 (the deleting variant) matches.
StateMachineWrapper::~StateMachineWrapper() {
    mMachine._0->m3(&mMachine.mPrevious);
    mMachine._0->m3(&mMachine.mCurrent);
}

void StateMachineWrapper::replaceState() {
    if (mMachine.mNextState) {
        mMachine.mCurrent = mMachine._0->setState(mMachine.mNextState);
        mMachine.mCurrent->enter();
        mMachine.mNextState = nullptr;
    }
}

// NON_MATCHING: the original calls setState() without loading an argument (x1 is left as it was on entry), so the
// source passed an uninitialised value; passing mNextState adds `ldp x0, x1`.
void StateMachineWrapper::changeStateFast() {
    mMachine.mCurrent = mMachine._0->setState(mMachine.mNextState);
    mMachine.mCurrent->enter();
}

void StateMachineWrapper::run() {
    mMachine.run();
}

void StateMachineWrapper::leaveState() {
    mMachine.sub_71010BFE64();
}

void StateMachineWrapper::enterState() {
    mMachine.mCurrent->enter();
}

void StateMachineWrapper::changeState(const ksys::StateBase* state) {
    mMachine.changeState(state);
}

const ksys::StateBase* StateMachineWrapper::getState() const {
    return mMachine.getState();
}

const ksys::StateBase* StateMachineWrapper::getSubstate() const {
    return mMachine.mPrevState;
}

s32 StateMachineWrapper::getRunCount() const {
    return mMachine.mCurrent->getRunCount();
}

bool StateMachineWrapper::reenter(void* arg) {
    if (!mMachine.mCurrent)
        StateMachineWrapper::replaceState();
    if (mMachine.mCurrent)
        return mMachine.mCurrent->reenter(arg);
    return false;
}

bool StateMachineWrapper::exec5(void* arg) {
    if (mMachine.mCurrent)
        return mMachine.mCurrent->exec5(arg);
    return false;
}

void StateMachineWrapper::exec6(void* arg) {
    if (mMachine.mCurrent)
        mMachine.mCurrent->exec6(arg);
}

// 0x71025cb530 (not written by any decompiled function yet; hidden visibility keeps the load from being folded and
// from going through the GOT, as the original addresses it directly)
KSYS_VISIBILITY_HIDDEN bool sIsFirstLaunch;

bool GameScene::getIsFirstLaunch() {
    return sIsFirstLaunch;
}

bool GameScene::m0(const sead::SafeString& name) {
    return m1(name, false);
}

bool GameScene::m1(const sead::SafeString& name, bool flag) {
    if (name.isEmpty()) {
        sub_71007B7D78();
    } else {
        _8.copy(name);
        _120 = flag;
        _121 = false;
    }
    return true;
}

bool GameScene::m2(const sead::SafeString& name, const sead::Vector3f& pos) {
    _8.copy(name);
    _120 = false;
    _121 = true;
    _124 = pos;
    _130.clear();
    return true;
}

bool GameScene::m3(const sead::SafeString& name, const sead::SafeString& name2) {
    _8.copy(name);
    _121 = true;
    _120 = false;
    _124.set(0, 0, 0);
    _130.copy(name2);
    if (_130.isEmpty())
        _121 = false;
    return true;
}

bool GameScene::getIsInitialisingStage() {
    return sIsInitialisingStage;
}

void GameScene::setInstance2() {
    sInstance2 = sInstance;
}

void GameScene::setInstance3() {
    sInstance3 = sInstance;
}

bool sceneStartEventReady() {
    return sSceneStartEventReady;
}

void setSceneStartEventReady() {
    sSceneStartEventReady = true;
}

void setSceneStartEventNotReady() {
    sSceneStartEventReady = false;
}

bool isTransitionFromFarActorDone() {
    return sIsTransitionFromFarActorDone;
}

void setIsTransitionFromFarActorDone(bool value) {
    sIsTransitionFromFarActorDone = value;
}

bool getIsStageUnloaded() {
    return sIsStageUnloaded;
}

void setIsStageUnloaded(bool value) {
    sIsStageUnloaded = value;
}

void gameSceneSetFlag(bool value) {
    GameScene::sFlag = value;
}

bool gameSceneGetFlag() {
    return GameScene::sFlag;
}

bool isGameSceneInitialized() {
    return GameScene::sInstance3 != nullptr;
}

const sead::SafeString& GameScene::getCurrentMapType() {
    return ksys::StageInfo::getCurrentMapType();
}

const sead::SafeString& GameScene::getCurrentMapName() {
    return ksys::StageInfo::getCurrentMapName();
}

bool GameScene::ret0() {
    return false;
}

void GameScene::m11_null() {}

void GameScene::StageMgrEnter() {}

void GameScene::StageMgrLeave() {}

bool GameScene::StageMgrReenter() {
    return false;
}

void GameScene::PatchErrorRun() {}

void GameScene::PatchErrorLeave() {}

bool GameScene::PatchErrorReenter() {
    return false;
}

void GameScene::StageSelectLeave() {}

bool GameScene::StageSelectReenter() {
    return false;
}

void GameScene::setFadeType(s32 type) {
    _93c = type;
}

bool GameScene::hasStageBinder() const {
    return _2a8 != nullptr;
}

void GameScene::LunchTitleLeave() {}

bool GameScene::LunchTitleReenter() {
    return false;
}

void GameScene::StageTransitionEnter() {}

void GameScene::StageTransitionRun() {}

void GameScene::StageTransitionLeave() {}

bool GameScene::StageTransitionReenter() {
    return false;
}

bool GameScene::NewSaveReenter() {
    return false;
}

void GameScene::setStageBinder(StageBinder* binder) {
    if (_2a8)
        return;
    _2a8 = binder;
    _279 |= 1;
}

}  // namespace uking
