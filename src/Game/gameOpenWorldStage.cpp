#include "Game/gameOpenWorldStage.h"
#include "Game/gameOpenWorldStageMessage.h"
#include "Game/gameStage.h"
#include "Game/Damage/dmgInfoManager.h"
#include "Game/gameHorseMgr.h"
#include "Game/gameLastBossMgr.h"
#include "Game/gameMotorcycleMgr.h"
#include "Game/gameScene.h"
#include "Game/gameSceneSubsys14.h"
#include "Game/gameSceneSubsysMisc.h"
#include "Game/gameWolfLinkMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/System/CameraMgr.h"
#include "KingSystem/Utils/Thread/MessageDispatcherBase.h"
#include "KingSystem/Utils/Thread/MessageBroker.h"
#include "Game/gameUnkRttiPlaceholders.h"

namespace uking {

bool OpenWorldStage::getMapName(sead::BufferedSafeString* out, int col, int row) {
    out->format("%c-%d/%c-%d", col + 'A', row + 1, col + 'A', row + 1);
    return true;
}

void OpenWorldStage::m4(int* col, int* row, const sead::SafeString& name) {
    *col = name[0] - 'A';
    *row = name[2] - '1';
}

void OpenWorldStage::getMapType(sead::BufferedSafeString* out) {
    out->copy(mMapType);
}

bool OpenWorldStage::m2(sead::BufferedSafeString* out) {
    ksys::act::Actor* actor = mPlayer;
    const float x = actor->getMtx().m[0][3];
    const float z = actor->getMtx().m[2][3];
    const int ix = int(x) + 5000;
    int col = ix / 1000;
    const int iz = int(z) + 4000;
    int row = iz / 1000;
    col = sead::Mathi::min(col, 9);
    int c;
    if (ix <= -1000)
        c = 0;
    else
        c = col;
    row = sead::Mathi::min(row, 7);
    int r;
    if (iz <= -1000)
        r = 0;
    else
        r = row;
    return getMapName(out, c, r);
}

void OpenWorldStage::postCalc() {
    dmg::DamageInfoMgr::instance()->postCalc();
    GameSceneSubsys4::instance()->m6();
    GameSceneSubsys5::instance()->postCalc();
    LastBossMgr::instance()->postCalc();
    GameSceneSubsys14::instance()->postCalc();
    if (GameScene::getCurrentMapType() != "AocField") {
        if (auto* mgr = HorseMgr::instance())
            mgr->postCalc();
    }
    if (auto* mgr = WolfLinkMgr::instance())
        mgr->postCalc();
    if (auto* mgr = MotorcycleMgr::instance())
        mgr->sub_7100678BD4();
}

void OpenWorldStage::initForStageGen() {
    ksys::world::sub_71010D6094(ksys::world::Manager::instance()->getEnvMgr());
}

s32 OpenWorldStage::getType() {
    return 0;
}

bool OpenWorldStage::unloadOk() {
    return true;
}

bool OpenWorldStage::ret0(void* arg) {
    return false;
}

void OpenWorldStage::m27_null(void* arg) {}

void OpenWorldStage::fieldEnter() {
    callRoot4Stuff();
    ksys::CameraMgr::instance()->sub_7100D8C488(0, mCamera);
    _1e0 = 0;
}

void OpenWorldStage::fieldRun() {}

void OpenWorldStage::fieldLeave() {}

bool OpenWorldStage::fieldReenter(void* arg) {
    return false;
}

OpenWorldStage::~OpenWorldStage() = default;

bool Unk_710245b478::return0(void* owner, void* arg) const {
    return static_cast<OpenWorldStage*>(owner)->ret0(arg);
}

void Unk_710245b478::null(void* owner, void* arg) const {
    static_cast<OpenWorldStage*>(owner)->m27_null(arg);
}

const ksys::StateBase& Unk_710245b740::getState() const {
    return *mState;
}

Unk_710245b710::~Unk_710245b710() = default;

// NON_MATCHING: the adapter address is computed before the dispatcher call.
Unk_710245b4f8::~Unk_710245b4f8() {
    deregisterReceiver(mAdapter);
}

bool Unk_710245b4f8::sendMessage(const ksys::MesTransceiverId& dest,
                                 const ksys::MessageType& type, void* user_data, bool ack) {
    const bool sent = getDispatcher()->sendMessage(*mAdapter.MessageReceiver::getId(), dest, type,
                                                  user_data, ack, false);
    if (sent)
        mAdapter.setFlag(ack);
    return sent;
}

bool Unk_710245b4f8::sendMessageOnProcessingThread(const ksys::MesTransceiverId& dest,
                                                   const ksys::MessageType& type, void* user_data,
                                                   bool ack) {
    const bool sent = getDispatcher()->sendMessageOnProcessingThread(
        *mAdapter.MessageReceiver::getId(), dest, type, user_data, ack, false);
    if (sent)
        mAdapter.setFlag(ack);
    return sent;
}

bool Unk_710245b4f8::sendMessage(ksys::IMessageBroker& broker, const ksys::MessageType& type,
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

bool Unk_710245b4f8::sendMessageOnProcessingThread(ksys::IMessageBroker& broker,
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

ksys::MessageReceiverEx* Unk_710245b4f8::getReceiver() {
    return &mAdapter;
}

// NON_MATCHING: the final state cleanup argument is scheduled before the frame restore.
Unk_710245b540::~Unk_710245b540() = default;

void Unk_710245b540::run() {
    mMachine.run();
}

// NON_MATCHING: the bool state callback result requires conversion to the receiver's int result.
int Unk_710245b540::receive(const ksys::Message& message) {
    if (Unk_710245b690::reenter(const_cast<ksys::Message*>(&message)))
        return 1;
    return Unk_710245b690::exec5(const_cast<ksys::Message*>(&message));
}

void Unk_710245b540::receive(const ksys::MessageAck& ack) {
    Unk_710245b690::exec6(const_cast<ksys::MessageAck*>(&ack));
}

void Unk_710245b740::enter() {
    mRunCount = 0;
    mState->enter(mOwner);
}

void Unk_710245b740::run() {
    mState->run(mOwner);
    ++mRunCount;
}

void Unk_710245b740::leave() {
    mState->leave(mOwner);
    mState = nullptr;
    mRunCount = 0;
}

ksys::StateMachine::Unk2* Unk_710245b710::setState(const ksys::StateBase* state) {
    mBinding.mState = state;
    return &mBinding;
}

void Unk_710245b690::replaceState() {
    if (mMachine.mNextState) {
        mMachine.mCurrent = mMachine._0->setState(mMachine.mNextState);
        mMachine.mCurrent->enter();
        mMachine.mNextState = nullptr;
    }
}

void Unk_710245b690::changeStateFast(const ksys::StateBase* state) {
    mMachine.mCurrent = mMachine._0->setState(state);
    mMachine.mCurrent->enter();
}

void Unk_710245b690::run() {
    mMachine.run();
}

void Unk_710245b690::leaveState() {
    mMachine.sub_71010BFE64();
}

void Unk_710245b690::enterState() {
    mMachine.mCurrent->enter();
}

void Unk_710245b690::changeState(const ksys::StateBase* state) {
    mMachine.changeState(state);
}

const ksys::StateBase* Unk_710245b690::getState() const {
    return mMachine.getState();
}

const ksys::StateBase* Unk_710245b690::getSubstate() const {
    return mMachine.mPrevState;
}

s32 Unk_710245b690::getRunCount() const {
    return mMachine.mCurrent->getRunCount();
}

bool Unk_710245b690::reenter(void* arg) {
    if (!mMachine.mCurrent)
        Unk_710245b690::replaceState();
    if (mMachine.mCurrent)
        return mMachine.mCurrent->reenter(arg);
    return false;
}

bool Unk_710245b690::exec5(void* arg) {
    if (mMachine.mCurrent)
        return mMachine.mCurrent->exec5(arg);
    return false;
}

void Unk_710245b690::exec6(void* arg) {
    if (mMachine.mCurrent)
        mMachine.mCurrent->exec6(arg);
}

}  // namespace uking

Unk_710245b3d8::~Unk_710245b3d8() = default;

Unk_710245b8a8::~Unk_710245b8a8() = default;

Unk_710245b7a0::~Unk_710245b7a0() = default;
