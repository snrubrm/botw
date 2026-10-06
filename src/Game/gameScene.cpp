#include "Game/gameScene.h"
#include "Game/gameSceneStateMachine.h"
#include "Game/gamePlayerResetPosMgr.h"
#include "Game/gameStageInfo.h"
#include "Game/gameStageBinder.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/Resource/resResource.h"
#include "Game/UI/euiScreen.h"
#include "Game/UI/uiScreens.h"

namespace uking {

// Internal-linkage globals of the GameScene TU (0x728 / 0x72c / 0x730; the original addresses them
// directly, not through the GOT).
static bool sSceneStartEventReady;
static bool sIsTransitionFromFarActorDone;
static bool sIsStageUnloaded;
static sead::FixedSafeString<0xff> sSceneChangeEventFlow;
static sead::FixedSafeString<0xff> sSceneChangeEventFlowEntryPoint;

// 0x71025cb0eb (not a TU-local: the original addresses it through the GOT)
bool sForceEnableGlidingSurfingRupee;

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
struct SceneStatics {
    bool isFirstLaunch;
    u8 _1[0x2b];
    s32 newSaveState_2c;
    u8 _30[0x2c];
    s32 newSaveState_5c;
};
KSYS_VISIBILITY_HIDDEN SceneStatics sSceneStatics;

bool GameScene::getIsFirstLaunch() {
    return sSceneStatics.isFirstLaunch;
}

bool GameScene::m0(const sead::SafeString& name) {
    return m1(name, false);
}

void GameScene::sub_71007B4B50() {
    _8ca = true;
    _6e9 = true;
    _2a8 = nullptr;
    _279 |= 1;
    PlayerResetPosMgr::instance()->resetSmallKeyFlags();
    PlayerResetPosMgr::instance()->clearResetPos();
    if (auto* actor_system = ksys::act::ActorSystem::instance())
        actor_system->set104(false);
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

bool GameScene::m5(const sead::SafeString& name, const sead::SafeString& name2) {
    sSceneChangeEventFlow.copy(name);
    sSceneChangeEventFlowEntryPoint.copy(name2);
    return true;
}

const sead::SafeString& getSceneChangeEventFlow() {
    return sSceneChangeEventFlow;
}

const sead::SafeString& getSceneChangeEventFlowEntryPoint() {
    return sSceneChangeEventFlowEntryPoint;
}

void setSceneChangeEventFlow(const sead::SafeString& flow, const sead::SafeString& entry_point) {
    sSceneChangeEventFlow.copy(flow);
    sSceneChangeEventFlowEntryPoint.copy(entry_point);
}

// The state objects are used through pointers: clang devirtualizes `sUnk.getId()` on the object itself (the original
// calls getId() through the vtable). The first half evaluates calls whose results are not used.
bool GameScene::m4() {
    PlayerResetPosMgr::instance()->isNotResetting();
    sead::DynamicCast<ui::Fade>(eui::ScreenMgr::instance()->getScreen(ui::ScreenId::Fade))->isClosed();
    if (!_6e7) {
        _1d0.getState()->getId();
        // called through a pointer in the original (not devirtualised)
        (&sUnk_71025cb150)->getId();
    }
    someEventMgrCheck();
    if (!_2a8 && _8.isEmpty() && _6e0 == 0 && PlayerResetPosMgr::instance()->isNotResetting()) {
        if (sead::DynamicCast<ui::Fade>(eui::ScreenMgr::instance()->getScreen(ui::ScreenId::Fade))->isClosed()) {
            // called through a pointer in the original (not devirtualised)
            if (!_6e7 && _1d0.getState()->getId() != (&sUnk_71025cb150)->getId())
                return false;
            if (!someEventMgrCheck())
                return true;
        }
    }
    return false;
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

void setForceEnableGlidingSurfingRupee(bool value) {
    sForceEnableGlidingSurfingRupee = value;
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

const sead::Vector3f& StageInfo::getPSavePosAngleForStageGen() {
    return sPSavePosAngleForStageGen;
}

const sead::Vector3f& StageInfo::getPSavePosForStageGen() {
    return sPSavePosForStageGen;
}

// NON_MATCHING: the original ends with a branch (`mov w0, wzr; b.pl; orr w0, wzr, #1`) where ours has `cset w0, mi`.
bool GameScene::canTriggerPanicBloodMoon() {
    if (ksys::StageInfo::sIsDungeon)
        return false;
    if (ksys::StageInfo::getCurrentMapType() == "AocField")
        return false;
    if (ksys::StageInfo::getCurrentMapType() == "GameTestField")
        return false;
    if (ksys::StageInfo::getCurrentMapType() == "GameTestField2")
        return false;
    if (ksys::StageInfo::sIsDebugOrDevMap)
        return false;
    if (getSceneStatus() != 0)
        return false;
    if (::ui::isFadeDemoOrFadeScreenOpened())
        return false;
    if (someEventMgrCheck())
        return false;
    if (ksys::evt::Manager::instance()->hasActiveEvent())
        return false;
    auto* player = ksys::act::PlayerInfo::instance()->getPlayer();
    if (!player)
        return false;
    sead::Vector3f save_pos;
    ksys::gdt::getFlag_PlayerSavePos(&save_pos, false);
    return (player->getMtx().getTranslation() - save_pos).squaredLength() < 0.25f;
}

bool GameScene::returnZero() {
    return false;
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

void GameScene::setNeedStageGenFinalStepInPreCalc() {
    _8cb = true;
}

bool GameScene::isNotNeedStageGenFinalStepInPreCalc() const {
    return !_8cb;
}

void GameScene::sub_71007B4BCC() {
    _944.setBitOn(0);
}

void GameScene::sub_71007B4BE4() {
    _944.setBitOff(0);
    _950.setSignal();
}

bool GameScene::sub_71007B4C00() const {
    return _948.isBitOn(1);
}

bool GameScene::sub_71007B0D3C() const {
    // called through a pointer in the original (not devirtualised)
    return _1d0.getState()->getId() == (&sUnk_71025cb150)->getId();
}

bool GameScene::hasStageBinder() const {
    return _2a8 != nullptr;
}

OpenWorldStageBinder* GameScene::createOpenWorldStageBinder() {
    if (!_288)
        return nullptr;
    return new (_288, 8) OpenWorldStageBinder;
}

ksys::res::Resource* GameScene::getEnvArchive() const {
    return sead::DynamicCast<ksys::res::Resource>(_2c0.getResource());
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

void GameScene::LunchTitleRun() {
    if (sSceneStatics.newSaveState_2c == 10)
        createTitleStageBinder(true, true);
    commonRun(false, false);
}

void GameScene::NewSaveLeave() {
    sSceneStatics.newSaveState_2c = 0;
    sSceneStatics.newSaveState_5c = 0;
    _320.reset();
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
