#pragma once

#include <container/seadBuffer.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/Attention/actAttClient.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {
class AttClientList;
}

namespace ksys::act {

class Actor;

// Name from the CSV (ActorAttention::make 0x7100d72dcc, ActorAttention::*): the per-actor
// attention object (Actor::mAttention), owning one AttClient per entry of the actor's
// AttClientList.
// TODO: incomplete.
class ActorAttention {
public:
    s32 getNumClients() const;
    // 0x7100d73430 (the const-qualified twin is at 0x7100d7340c; not decompiled).
    AttClient* getClientByIdx(s32 idx);
    const AttClient* getClientByIdx(s32 idx) const;
    // 0x7100d732c4 / 0x7100d7317c (two identical copies; which one is const is a guess).
    AttClient* getClientByName(const sead::SafeString& name);
    const AttClient* getClientByName(const sead::SafeString& name) const;
    // 0x7100d73470 / 0x7100d735d4 / 0x7100d73728: the client called `name`.
    bool isClientEnabled(const sead::SafeString& name) const;
    bool enableClient(const sead::SafeString& name);
    bool disableClient(const sead::SafeString& name);
    void enableAllClients();
    void disableAllClients();

    /* 0x00 */ res::AttClientList* mList;
    /* 0x08 */ Actor* mActor;
    /* 0x10 */ sead::Buffer<AttClient> mClients;
};

}  // namespace ksys::act
