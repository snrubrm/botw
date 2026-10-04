#include "Game/gameSceneTaskMgr.h"

namespace uking {

Invoker2::Invoker2(Function function) {
    mCallable = new (mStorage) Callable(function);
}

Invoker2::~Invoker2() {
    if (mCallable)
        mCallable->~Callable();
}

void Invoker2::Callable::invoke() {
    if (mFunction)
        mFunction();
}

Invoker2::Callable* Invoker2::Callable::copyTo(void* storage) const {
    if (!mFunction)
        return nullptr;
    return new (storage) Callable(mFunction);
}

GameSceneTaskMgr::GameSceneTaskMgr() = default;

GameSceneTaskMgr::~GameSceneTaskMgr() = default;

void GameSceneTaskMgr::init(const sead::SafeString& thread_name, sead::Heap* heap,
                            sead::CoreId core, s32 priority) {
    mThread = new (heap) ksys::util::GameTaskThread(thread_name, heap, priority,
                                                    sead::MessageQueue::BlockType::Blocking,
                                                    0x7fffffff, 0x40000, 32);

    ksys::util::TaskThread::InitArg arg;
    arg.batch_size = 0;
    arg.heap = nullptr;
    arg.queue = nullptr;
    arg.num_lanes = 1;
    arg.heap = heap;
    mThread->init(arg);
    mThread->setAffinity(sead::CoreIdMask(core));
    mThread->start();

    mDelegate = new (heap)
        ksys::util::TaskDelegateT<GameSceneTaskMgr>(this, &GameSceneTaskMgr::invokeInvoker);
    mTask = new (heap) ksys::util::Task(heap);
    ksys::util::TaskDelegateSetter setter;
    setter.setDelegate(mDelegate);
    mTask->setDelegate(setter);
}

bool GameSceneTaskMgr::invokeInvoker(void*) {
    if (mInvoker.getCallable())
        mInvoker.getCallable()->invoke();
    return true;
}

}  // namespace uking
