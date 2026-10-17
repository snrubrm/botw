#include "Game/Scene/gameScene.h"
#include "Game/E3Mgr.h"
#include "Game/gameTipsMgr.h"
#include "Game/gameResidentActorMgr.h"
#include "Game/Actor/Damage/dmgInfoManager.h"
#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "Game/AutoPlacement/AutoPlacementFlowMgr.h"
#include "KingSystem/System/StarterPackMgr.h"
#include "KingSystem/Utils/HeapUtil.h"
#include "KingSystem/System/GameTool.h"
#include "KingSystem/System/MoviePlayer.h"
#include <layer/aglLayer.h>
#include "Game/gameDebugStatus.h"
#include "Game/gameSceneStatusMgr.h"
#include "KingSystem/ksys.h"
#include <devenv/seadGameConfig.h>
#include <prim/seadDelegate.h>
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "Game/gameSceneStateMachine.h"
#include "Game/gameSceneMessage.h"

void GameScene_Debug::fnStubbed() {}
#include "Game/gamePlayerResetPosMgr.h"
#include "Game/Scene/gameStageInfo.h"
#include "Game/gameStageBinder.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtEventFlow.h"
#include "Game/gameStage.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/Resource/resResource.h"
#include "Game/UI/euiScreen.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/System/UI/LayoutResourceMgr.h"
#include "KingSystem/Utils/Thread/MessageBroker.h"
#include "Game/gameUnkRttiPlaceholders.h"

Unk_71025d1740* Unk_71025d1740::sInstance;

namespace uking {

Unk_710245a528::~Unk_710245a528() = default;

// NON_MATCHING: the inferred s32 category return clears W0; native clears X0.
s32 Unk_710245a528::getType() const {
    return 0;
}

// NON_MATCHING: the base zero stores are ordered differently around the vtable initialization.
GameScene::sb::sb() = default;

GameScene::sb::~sb() {
    clear();
}

void GameScene::sb::x(s32 index, agl::lyr::Layer* layer, s32 step) {
    layer->sub_7100B60B8C(step, at(index));
}

GameScene::sc::sc() = default;

// NON_MATCHING: the loop updates the remaining count before the record pointer (ours: the other way round).
GameScene::sc::~sc() {
    for (auto& record : mRecords) {
        void* unused;
        record.sub_7100FE7FBC(&unused);
    }
    mRecords.freeBuffer();
    mFlags &= ~4;
}

bool GameScene::sc::x_0() const {
    return (mFlags >> 2) & 1;
}


void GameScene::PatchErrorEnter() {
    Unk_71025d1740::instance()->sub_7100901A90(true);
}

// Internal-linkage globals of the GameScene TU (0x728 / 0x72c / 0x730; the original addresses them
// directly, not through the GOT).
static bool sSceneStartEventReady;
static bool sIsTransitionFromFarActorDone;
static bool sIsStageUnloaded;
static sead::FixedSafeString<0xff> sSceneChangeEventFlow;
static sead::FixedSafeString<0xff> sSceneChangeEventFlowEntryPoint;

// 0x71025cb0eb (not a TU-local: the original addresses it through the GOT)
bool sForceEnableGlidingSurfingRupee;

// 0x71025cb0e8 (also addressed through the GOT; unnamed). Set by setIsRestartStageFromGameOver (the
// restart-from-game-over request), cleared by genStage / resetStage and read by PlayerInfo::updateLifeAfterGameOver.
bool sIsRestartStageFromGameOver;

// 0x710245a360 (also addressed through the GOT; unnamed). Written by setIsRestartStageFromGameOver and read /
// written by many of the stage generation functions.
bool sUnk_710245a360;

// External-linkage flag: initialize clears it, preCalcStageMgrOrSelectHandleStageChanges sets it.
bool sUnk_71025cb0ed;

bool GameScene::sIsOpenWorldDemo{};
GameScene* GameScene::sInstance;
bool GameScene::sIsInitialisingStage;
GameScene* GameScene::sInstance2;
GameScene* GameScene::sInstance3;
bool GameScene::sFlag;

bool GameSceneStateBase::return0(void* owner, void* arg) const {
    return static_cast<GameScene*>(owner)->ret0(arg);
}

void GameSceneStateBase::null(void* owner, void* arg) const {
    static_cast<GameScene*>(owner)->m11_null(arg);
}

const ksys::StateBase& StateMachineOwnerBinding::getState() const {
    return *mState;
}

StateMachineOwnerBinding::~StateMachineOwnerBinding() = default;

Unk_710245a688::~Unk_710245a688() {
    getDispatcher()->deregisterTransceiver(mAdapter);
}

bool Unk_710245a688::sendMessage(const ksys::MesTransceiverId& dest,
                                const ksys::MessageType& type, void* user_data, bool ack) {
    const bool sent = getDispatcher()->sendMessage(*mAdapter.MessageReceiver::getId(), dest, type,
                                                  user_data, ack, false);
    if (sent)
        mAdapter.setFlag(ack);
    return sent;
}

bool Unk_710245a688::sendMessageOnProcessingThread(const ksys::MesTransceiverId& dest,
                                                 const ksys::MessageType& type, void* user_data,
                                                 bool ack) {
    const bool sent = getDispatcher()->sendMessageOnProcessingThread(
        *mAdapter.MessageReceiver::getId(), dest, type, user_data, ack, false);
    if (sent)
        mAdapter.setFlag(ack);
    return sent;
}

bool Unk_710245a688::sendMessage(ksys::IMessageBroker& broker, const ksys::MessageType& type,
                                void* user_data, bool ack) {
    const bool sent = getDispatcher()->sendMessage(*mAdapter.MessageReceiver::getId(),
                                                  *getRegister(broker), type, user_data, ack, false);
    if (sent) {
        int count = broker.countTransceivers();
        if (count > 0) {
            do {
                mAdapter.setFlag(ack);
            } while (--count);
        }
    }
    return sent;
}

bool Unk_710245a688::sendMessageOnProcessingThread(ksys::IMessageBroker& broker,
                                                 const ksys::MessageType& type, void* user_data,
                                                 bool ack) {
    const bool sent = getDispatcher()->sendMessageOnProcessingThread(
        *mAdapter.MessageReceiver::getId(), *getRegister(broker), type, user_data, ack, false);
    if (sent) {
        int count = broker.countTransceivers();
        if (count > 0) {
            do {
                mAdapter.setFlag(ack);
            } while (--count);
        }
    }
    return sent;
}

ksys::MessageReceiverEx* Unk_710245a688::getReceiver() {
    return &mAdapter;
}

// NON_MATCHING: the final state cleanup argument is scheduled before the frame restore.
Unk_710245a7a0::~Unk_710245a7a0() = default;

Unk_710245a6d0::~Unk_710245a6d0() = default;

void Unk_710245a6d0::run() {
    mMachine.run();
}

// NON_MATCHING: the bool state callback result requires conversion to the receiver's int result.
int Unk_710245a6d0::receive(const ksys::Message& message) {
    if (StateMachineWrapper::reenter(const_cast<ksys::Message*>(&message)))
        return 1;
    return StateMachineWrapper::exec5(const_cast<ksys::Message*>(&message));
}

void Unk_710245a6d0::receive(const ksys::MessageAck& ack) {
    StateMachineWrapper::exec6(const_cast<ksys::MessageAck*>(&ack));
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

void StateMachineWrapper::replaceState() {
    if (mMachine.mNextState) {
        mMachine.mCurrent = mMachine._0->setState(mMachine.mNextState);
        mMachine.mCurrent->enter();
        mMachine.mNextState = nullptr;
    }
}

void StateMachineWrapper::changeStateFast(const ksys::StateBase* state) {
    mMachine.mCurrent = mMachine._0->setState(state);
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
    u8 _1[4];
    bool _5;  // set by sub_71007B4C28 (game over)
    u8 _6;
    u8 _7;
    bool _8;
    u8 _9[0x2c - 9];
    s32 newSaveState_2c;
    u8 _30[0x2c];
    s32 newSaveState_5c;
    s32 _60;  // cleared by sub_71007B4C28
};
KSYS_VISIBILITY_HIDDEN SceneStatics sSceneStatics;

// The scene initializer builds the LunchTitle state with GameScene callbacks.
extern GameSceneStateBase sUnk_71025cb210;

// Set after genStage starts Demo169_0; cleared by the final stage step.
// The original addresses this scene global directly, like sSceneStatics.
KSYS_VISIBILITY_HIDDEN bool sUnk_71025cb0d8;

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

// NON_MATCHING: the existing Damage interface consumes no heap argument; the native caller loads one.
void GameScene::initGlobalParamE3TipsActorAndPlacement() {
    if (ksys::util::getDebugHeap())
        ksys::StarterPackMgr::instance()->loadTitlePack();
    ksys::act::GlobalParameter::createInstance(_280);
    if (auto* parameters = ksys::act::GlobalParameter::instance()) {
        parameters->init(_280);
        parameters->loadActorPack(_280);
    }
    E3Mgr::instance()->loadBuildTimeStubbed();
    TipsMgr::instance()->loadTipFiles();
    ResidentActorMgr::instance()->loadByml();
    uking::AutoPlacementFlowMgr::instance()->loadEventFlows();
    if (act::DamageInfoMgr::instance())
        act::DamageInfoMgr::instance()->sub_7100673D8C();
}

// 0x71025cb334 (placeholder name): counts the calls of areResourcesReadyMaybe (nothing else reads it).
KSYS_VISIBILITY_HIDDEN s32 sUnk_71025cb334;

bool GameScene::areResourcesReadyMaybe() {
    ++sUnk_71025cb334;
    if (auto* parameters = ksys::act::GlobalParameter::instance()) {
        if (!parameters->isActorPackReady())
            return false;
    }
    if (!E3Mgr::instance()->resIsReady())
        return false;
    if (!TipsMgr::instance()->areResourcesReady())
        return false;
    if (!ResidentActorMgr::instance()->resIsReady())
        return false;
    if (!uking::AutoPlacementFlowMgr::instance()->resAreReady())
        return false;
    if (auto* damage = act::DamageInfoMgr::instance()) {
        if (!damage->isReady())
            return false;
    }
    if (ksys::StarterPackMgr::instance()->failedLoadTitlePack() &&
        !ksys::StarterPackMgr::instance()->isTitlePackReady())
        return false;
    return true;
}

}  // namespace uking

bool sub_71007AF558() {
    return uking::sForceEnableGlidingSurfingRupee && !sead::GameConfig::instance()->get_81a();
}

void setIsRestartStageFromGameOver() {
    uking::sUnk_710245a360 = true;
    uking::sIsRestartStageFromGameOver = true;
    if (sub_71007AF558()) {
        uking::recoverLifeAndStamina();
        uking::sIsRestartStageFromGameOver = false;
    }
}

namespace uking {

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
    auto* player = uking::act::PlayerInfo::instance()->getPlayer();
    if (!player)
        return false;
    sead::Vector3f save_pos;
    ksys::gdt::getFlag_PlayerSavePos(&save_pos, false);
    return (player->getMtx().getTranslation() - save_pos).squaredLength() < 0.25f;
}

bool GameScene::returnZero() {
    return false;
}

bool GameScene::ret0(void*) {
    return false;
}

void GameScene::m11_null(void*) {}

void GameScene::StageMgrEnter() {}

void GameScene::StageMgrRun() {
    bool flag;
    if (auto* tool = ksys::GameTool::instance(); tool && tool->_54.isOnBit(0))
        flag = true;
    else
        flag = sUnk_71025cb0ed;

    if ((_279 & 1) == 0)
        return;
    _279 &= ~1;
    _6e0 = 1;
    _6e4 = flag;

    if (auto* movie = ksys::MoviePlayer::instance(); movie && movie->_31)
        movie->sub_71010B9C04();
    if (auto* actors = ksys::act::ActorSystem::instance()) {
        actors->invokeAutoPlacementMgrInvoker3();
        actors->invokeRadarMgrInvoker();
    }
}

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

// 0x71025cb348 (placeholder name): a DebugStatus of this TU, constructed by its static initialiser
// (not decompiled; declaration only).
extern DebugStatus sUnk_71025CB348;

void GameScene::sub_71007B4C28() {
    if (sub_71007AF558())
        return;
    ksys::setIsGameOver(true);
    sSceneStatics._5 = true;
    sSceneStatics._60 = 0;
    sUnk_71025CB348.clear();
    sUnk_71025CB348.startTimer();
    if (auto* mgr = GameSceneStatusMgr::instance())
        mgr->registerStatus(&sUnk_71025CB348);
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

void GameScene::NewSaveRun() {
    if (++sSceneStatics.newSaveState_5c <= 90) {
        sSceneStatics.newSaveState_2c = 0;
        if (_320._8) {
            _320.sub_71008979E4();
            if (_320.sub_7100897A60())
                _1d0.changeState(&sUnk_71025cb210);
        }
        return;
    }
    if (sSceneStatics.newSaveState_2c == 9)
        ui::ScreenTitle::sub_7100A6B178(false);
    else if (sSceneStatics.newSaveState_2c == 10)
        calledFromNewSaveRun_10();
    if (sUnk_71025cb0d8 && ksys::evt::Manager::instance()->getActiveEvent()) {
        // The original retains the string's two termination calls, discarding the comparison.
        ksys::evt::Manager::instance()->getActiveEvent()->mEventName == "Demo169_0";
    }
    commonRun(true, false);
}

void GameScene::NewSaveLeave() {
    sSceneStatics.newSaveState_2c = 0;
    sSceneStatics.newSaveState_5c = 0;
    _320.reset();
}

bool GameScene::NewSaveReenter() {
    return false;
}

// 0x71025cb8a0 (a position that GameScene::initialize sets; placeholder name)
sead::Vector3f sUnk_71025cb8a0;

// 0x71007b1110 (CSV name)
// NON_MATCHING: the original branches on the first flag (`b.ne`) instead of selecting with `cset`
bool gameSceneStartedBgProcessingAndNotFinished() {
    if (sSceneStatics._7 == 1)
        return !sSceneStatics._8;
    return false;
}

// 0x71007b7e7c (CSV name)
void pauseMenuDataMgrInitForNewSave() {
    ui::PauseMenuDataMgr::instance()->initForNewSave();
}

// The stage change hooks of the scene (0x71007b8054-0x71007b80a8): the first argument is the object at
// GameScene + 0x2b8, the stage type 3 is the title stage.
// 0x71007b8054 (CSV name)
void loadLayoutArchiveForTitle(void* a1, sead::Heap* heap, s32 type) {
    if (type == 3)
        ksys::ui::LayoutResourceMgr::instance()->loadTitleLayout(heap);
}

// 0x71007b8070 (CSV name)
void postStageUnloadResetLayoutResMgr(void* a1, s32 type) {
    if (type == 3)
        ksys::ui::LayoutResourceMgr::instance()->unloadTitleLayout();
}

// 0x71007b808c (CSV name)
bool stageSpecificResourceLoaded(void* a1, s32 type) {
    if (type == 3)
        return ksys::ui::LayoutResourceMgr::instance()->loadTitleLayoutResource();
    return true;
}

// 0x71007bea48 (CSV name)
void setSomePosition(const sead::Vector3f* position) {
    sUnk_71025cb8a0 = *position;
}

void GameScene::setStageBinder(StageBinder* binder) {
    if (_2a8)
        return;
    _2a8 = binder;
    _279 |= 1;
}

// NON_MATCHING: the base pool cleanup inlines instead of remaining a separate call.
Unk_710245a980::~Unk_710245a980() = default;

}  // namespace uking

// A function-pointer delegate on a BaseProc (CSV BaseProcInvoker; vtable 0x710245a5d8: invoke 0x7b66ac, clone 0x7b66c0,
// the shared isNoDummy 0xec4c0): its out-of-line copies are emitted in this TU.
template class sead::Delegate1Func<ksys::act::BaseProc*>;

Unk_7102513d70::~Unk_7102513d70() = default;

// Constant virtuals in the GameScene address range (placeholder names, no data references).
s32 sub_71007A7590() { return 1; }
void* sub_71007A7598() { return nullptr; }
s32 sub_71007A7744() { return 1; }
void* sub_71007A774C() { return nullptr; }
s32 sub_71007A7808() { return 1; }
void* sub_71007A7810() { return nullptr; }
