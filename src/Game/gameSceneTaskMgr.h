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

    class CallableBase {
    public:
        virtual ~CallableBase() = default;
        virtual void invoke() = 0;
        virtual CallableBase* copyTo(void* storage) const = 0;
    };

    // Stores a plain function pointer (vtable 0x710245bd98, no RTTI).
    class Callable : public CallableBase {
    public:
        explicit Callable(Function function) : mFunction(function) {}
        ~Callable() override = default;
        void invoke() override;
        Callable* copyTo(void* storage) const override;

    private:
        Function mFunction;
    };

    // The GameScene callable at 0x710245aab8 stores its receiver and a member pointer.
    template <typename T>
    class MemberCallable : public CallableBase {
    public:
        using MemberFunction = void (T::*)();
        MemberCallable(T* object, MemberFunction function) : mObject(object), mFunction(function) {}
        void invoke() override { (mObject->*mFunction)(); }
        MemberCallable* copyTo(void* storage) const override {
            return new (storage) MemberCallable(mObject, mFunction);
        }
    private:
        T* mObject;
        MemberFunction mFunction;
    };

    explicit Invoker2(Function function);
    template <typename T>
    Invoker2(T* object, void (T::*function)()) {
        mCallable = new (mStorage) MemberCallable<T>(object, function);
    }
    ~Invoker2();

    CallableBase* getCallable() const { return mCallable; }

private:
    friend class GameSceneTaskMgr;

    Invoker2() = default;

    alignas(8) u8 mStorage[0x40]{};
    CallableBase* mCallable{};
};
KSYS_CHECK_SIZE_NX150(Invoker2, 0x48);

// Placeholder name: the result of GameSceneTaskMgr::submitRequest, a wrapper of the submitted task (a null task
// counts as complete). Its constructor and destructor are out-of-line in the original (0x71007cb53c / 0x71007cb544).
class GameSceneTaskHandle {
public:
    GameSceneTaskHandle();
    ~GameSceneTaskHandle();

    // 0x71007cb548
    bool isComplete() const;

    ksys::Task* mTask;
};

// Runs invokers on a task thread (CSV GameSceneTaskMgr; the name is the CSV's).
class GameSceneTaskMgr {
public:
    GameSceneTaskMgr();
    ~GameSceneTaskMgr();

    void init(const sead::SafeString& thread_name, sead::Heap* heap, sead::CoreId core,
              s32 priority);
    bool invokeInvoker(void*);
    // 0x71007cb780: copies the invoker and runs it on the thread (asynchronously)
    GameSceneTaskHandle submitRequest(const Invoker2& invoker);

private:
    ksys::GameTaskThread* mThread{};
    ksys::Task* mTask{};
    ksys::TaskDelegate* mDelegate{};
    Invoker2 mInvoker;
};
KSYS_CHECK_SIZE_NX150(GameSceneTaskMgr, 0x60);

}  // namespace uking
