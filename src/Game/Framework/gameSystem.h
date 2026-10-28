#pragma once

#include <basis/seadTypes.h>
#include <heap/seadHeap.h>
#include <hostio/seadHostIONode.h>
#include "Game/Framework/gameSystemStruct1.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Framework;
}

namespace uking {
class GameScene;
}

namespace uking::frm {

// Vtable 0x710245c490: hostio::Node::getNodeClassType, the two sead RTTI virtuals and the
// destructor pair. RootTask::calc allocates 0xb0 bytes for it, then constructs the scene.
class System : public sead::hostio::Node {
public:
    SEAD_RTTI_BASE(System)
    System();
    virtual ~System();

    // 0x71007d1e3c: true while the scene does not exist yet, otherwise the scene's own check.
    bool isReady();
    // 0x71007d1e50: runs the bootup resource loading once the scene exists.
    void finalizeBootup();
    // 0x71007d1e60 / 0x71007d1e8c / 0x71007d1ee0: the frame-step wrappers. The framework
    // pointer is only forwarded to the scene.
    void preCalc(sead::Framework* const& framework);
    void calcAndRunStateMachine(sead::Framework* const& framework);
    void postCalc(sead::Framework* const& framework);

    /* 0x08 */ sead::Heap* mHeap = nullptr;
    /* 0x10 */ GameScene* mScene = nullptr;
    /* 0x18 */ SystemStruct1 mStruct1;
};
KSYS_CHECK_SIZE_NX150(System, 0xb0);

}  // namespace uking::frm
