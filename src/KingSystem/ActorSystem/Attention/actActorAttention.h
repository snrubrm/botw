#pragma once

#include <container/seadBuffer.h>
#include <math/seadVector.h>
#include <gsys/gsysModelAccessKey.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/Attention/actAttClient.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {
class AttClientList;
}

namespace ksys::act {

class Actor;
class ActorParam;

// Name from the CSV (ActorAttention::make 0x7100d72dcc, ActorAttention::*): the per-actor
// attention object (Actor::mAttention), owning one AttClient per entry of the actor's
// AttClientList.
// TODO: incomplete.
class ActorAttention {
public:
    // lane4 s85: the argument of make() (Actor::postCreateInit builds it on the stack).
    struct CreateArg {
        const ActorParam* param;
        sead::Heap* heap;
        Actor* actor;
    };

    // 0x7100d72dcc (CSV ActorAttention::make): nullptr when the actor has no AttClientList or a client fails to
    // initialise.
    static ActorAttention* make(const CreateArg& arg);

    // 0x7100d72d64 (the Buffer<AttClient> is freed before the bone key is destroyed).
    ~ActorAttention();

    // 0x7100d72fec (CSV ActorAttention::init)
    void init();

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
    // 0x7100d738ec / 0x7100d73924 / 0x7100d7395c / 0x7100d73994: call the matching operation on every client
    // (AttClient::sub_7100D72178 / sub_7100D721C0 / sub_7100D72320 / resetEnabled).
    void sub_7100D738EC();
    void sub_7100D73924();
    void sub_7100D7395C();
    void resetEnabled();
    // 0x7100d73454: `mList->x(out, mActor, &_50)` (the position of the attention target; Actor::m88 stores it).
    void sub_7100D73454(sead::Vector3f* out) const;

    /* 0x00 */ res::AttClientList* mList = nullptr;
    /* 0x08 */ Actor* mActor = nullptr;
    /* 0x10 */ sead::Buffer<AttClient> mClients;
    /* 0x20 */ gsys::BoneAccessKeyEx mBoneKey;
    // lane4 s85 (placeholder name): set by init() from the clients' maxima and the main body extent
    // (1000 when no client has a positive one, 0 without clients).
    /* 0x58 */ f32 _58 = -1.0f;
};
KSYS_CHECK_SIZE_NX150(ActorAttention, 0x60);

}  // namespace ksys::act
