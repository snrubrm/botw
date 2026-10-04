#pragma once

#include <basis/seadTypes.h>
#include <heap/seadHeap.h>
#include <mc/seadCoreInfo.h>
#include <new>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Thread/GameTaskThread.h"
#include "KingSystem/Utils/Thread/Task.h"
#include "KingSystem/Utils/Types.h"

namespace uking {

// A type-erased `void ()` callable with 0x40 bytes of in-place storage (CSV Invoker2; the class names
// and the split into holder and callable are guesses based on the layout of the original: the
// holder's constructor places the callable at the start of the storage and keeps a pointer to it).
class Invoker2 {
public:
    using Function = void (*)();

    // The only callable: stores a plain function pointer (vtable 0x710245bd98, no RTTI).
    class Callable {
    public:
        explicit Callable(Function function) : mFunction(function) {}
        virtual ~Callable() = default;
        virtual void invoke();
        virtual Callable* copyTo(void* storage) const;

    private:
        Function mFunction;
    };

    explicit Invoker2(Function function);
    ~Invoker2();

    Callable* getCallable() const { return mCallable; }

private:
    friend class GameSceneTaskMgr;

    Invoker2() = default;

    alignas(8) u8 mStorage[0x40]{};
    Callable* mCallable{};
};
KSYS_CHECK_SIZE_NX150(Invoker2, 0x48);

// Runs invokers on a task thread (CSV GameSceneTaskMgr; the name is the CSV's).
class GameSceneTaskMgr {
public:
    GameSceneTaskMgr();
    ~GameSceneTaskMgr();

    void init(const sead::SafeString& thread_name, sead::Heap* heap, sead::CoreId core,
              s32 priority);
    bool invokeInvoker(void*);

private:
    ksys::util::GameTaskThread* mThread{};
    ksys::util::Task* mTask{};
    ksys::util::TaskDelegate* mDelegate{};
    Invoker2 mInvoker;
};
KSYS_CHECK_SIZE_NX150(GameSceneTaskMgr, 0x60);

}  // namespace uking
