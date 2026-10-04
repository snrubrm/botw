#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/Utils/Thread/Message.h"

namespace ksys::act {
class Actor;
}

namespace uking {

// StasisMgr's secondary interface at +0x10, stored in ActorSystem at +0xc8.
// The placeholder name refers to its secondary vtable; the interface has five slots and no
// virtual destructor. The StasisMgr constructor installs this interface in ActorSystem.
class Unk_710243c7c8 {
public:
    virtual s32 m0(ksys::act::Actor* actor, void* request) = 0;
    virtual bool sendMessage(ksys::act::Actor* actor, ksys::MessageType type,
                             bool on_processing_thread) = 0;
    virtual s32 m2(const sead::Matrix34f& mtx) = 0;
    virtual s32 m3(const sead::Matrix34f& mtx, s32 index) = 0;
    virtual void* m4(ksys::act::Actor* actor) = 0;
};

}  // namespace uking
