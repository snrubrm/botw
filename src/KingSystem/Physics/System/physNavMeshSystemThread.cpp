#include "KingSystem/Physics/System/physHavokAI.h"

namespace ksys::phys {

// NON_MATCHING: the store of _108 is scheduled after the message constant (scheduling only)
void NavMeshSystemThread::sub_7100F895FC(f32 dt) {
    if (_10c)
        return;
    _108 += dt;
    // 'step'
    sendMessage(0x73746570, sead::MessageQueue::BlockType::NonBlocking);
}

}  // namespace ksys::phys
