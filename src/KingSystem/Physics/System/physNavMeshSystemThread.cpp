#include "KingSystem/Physics/System/physHavokAI.h"
#include <thread/seadThreadUtil.h>

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

}  // namespace ksys::phys
