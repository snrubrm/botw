#include "KingSystem/Physics/System/physHavokAI.h"
#include <thread/seadThreadUtil.h>
#include <time/seadTickTime.h>
#include <prim/seadNamable.h>
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

// NON_MATCHING: the two control-field stores precede the vtable stores.
NavMeshSystemThread::NavMeshSystemThread(HavokAI* system, sead::Heap* heap)
    : Thread("NavMeshSystemThread", heap, sead::ThreadUtil::ConvertPrioritySeadToPlatform(20),
             sead::MessageQueue::BlockType::Blocking, 0x7fffffff, 0x80000, 2),
      _100(system) {
    _108 = 0.0f;
    _10c = false;
    sead::CoreIdMask affinity;
    affinity.setOn(sead::CoreId::cSub1);
    setAffinity(affinity);
    sendMessage(0x696e6974, sead::MessageQueue::BlockType::NonBlocking);
}

// NON_MATCHING: the store of _108 is scheduled after the message constant (scheduling only)
void NavMeshSystemThread::sub_7100F895FC(f32 dt) {
    if (_10c)
        return;
    _108 += dt;
    // 'step'
    sendMessage(0x73746570, sead::MessageQueue::BlockType::NonBlocking);
}

// NON_MATCHING: INamable setup precedes the System singleton load in the init branch.
void NavMeshSystemThread::calc_(sead::MessageQueue::Element msg) {
    if (msg == 0x696e6974) {
        sead::INamable name("navmesh_system");
        System::instance()->runJobsMaybe(&name);
        return;
    }
    if (!_10c) {
        const f32 dt = _108;
        _108 = 0.0f;
        if (dt > 0.0f)
            _100->sub_7100F81550(dt);
    }
}

void NavMeshSystemThread::sub_7100F8962C() {
    sead::Thread* current = sead::ThreadMgr::instance()->getCurrentThread();
    _10c = true;
    setPriority(current->getPriority());
    const sead::TickTime start;
    if (mMessageQueue.peek(sead::MessageQueue::BlockType::NonBlocking) != 0) {
        const auto timeout = sead::TickSpan::makeFromSeconds(1);
        const auto interval = sead::TickSpan::makeFromMicroSeconds(100);
        do {
            if (start.diffToNow().toS64() > timeout.toS64()) {
                _100->sub_7100F84194();
                break;
            }
            sead::Thread::sleep(interval);
        } while (mMessageQueue.peek(sead::MessageQueue::BlockType::NonBlocking) != 0);
    }
    setPriority(sead::ThreadUtil::ConvertPrioritySeadToPlatform(20));
}

}  // namespace ksys::phys
