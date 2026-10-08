#include "KingSystem/Utils/Thread/GameTaskThread.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::util {

GameTaskThread::GameTaskThread(const sead::SafeString& name, sead::Heap* heap, s32 priority,
                               sead::MessageQueue::BlockType block_type, long quit_msg,
                               s32 stack_size, s32 message_queue_size)
    : TaskThread(name, heap, priority, block_type, quit_msg, stack_size, message_queue_size) {}

void GameTaskThread::quit(bool) {
    mMessageQueue.push(cMessage_GameThreadQuit, sead::MessageQueue::BlockType::Blocking);
    Thread::quit(false);
}

void GameTaskThread::calc_(sead::MessageQueue::Element msg) {
    if (_1a0 & 1)
        return;
    if (msg == cMessage_GameThreadQuit) {
        if (_1a4 != -1) {
            phys::System::instance()->sub_71012157B4(nullptr, false);
            _1a4 = -1;
        }
        _1a0 |= 1;
        return;
    }
    if (_1a4 == -1) {
        if (auto* system = phys::System::instance())
            _1a4 = system->runJobsMaybe(this);
    }
    TaskThread::calc_(msg);
}

}  // namespace ksys::util
