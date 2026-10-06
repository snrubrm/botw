#pragma once

#include "KingSystem/ActorSystem/Attention/actAttention.h"
#include <container/seadBuffer.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/Actor/resResourceAttClient.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class Actor;
class BaseProc;

// TODO: incomplete
class AttClient {
public:
    // 0x0000007100d71170
    AttClient();
    // 0x7100d71248
    ~AttClient();

    const sead::SafeString& getName() const;
    void resetEnabled();
    void enable();
    void disable();
    void setEnabled(bool enabled);
    bool isEnabled() const;
    // 0x7100d724fc / 0x7100d7250c: `_54 |= flags` / `_54 &= ~flags` (PriestBossEyeBeam::enter_ / leave_ pass 1).
    void sub_7100D724FC(u32 flags);
    void sub_7100D7250C(u32 flags);
    void setCallback(void* callback);
    // 0x7100d72554: whether the client's checks pass for `proc` (NameBalloon: never; Appeal:
    // camera within 30 of the actor).
    bool sub_7100D72554(BaseProc* proc, const res::AttCheck_Unk1* arg, bool a3) const;
    // 0x7100d72534: a value of the client's resource (`_8->_a0->_2b0`).
    s32 sub_7100D72534() const;
    // 0x7100d721c0: declaration-only attention update operation.
    void sub_7100D721C0();
    // 0x7100d72178 (CSV AttClient::x_3; declaration only): copies the matrix data of the resource client (reads the
    // Attention singleton) into `_48..` and runs AttClient::checkM4.
    void sub_7100D72178();
    // 0x7100d72320 (CSV AttClient::x_2): registers the client with the Attention singleton.
    void sub_7100D72320();
    // 0x7100d72144: whether the client has an actor and a resource client.
    bool sub_7100D72144() const;
    // 0x7100d7235c: `_30 = value`.
    void sub_7100D7235C(void* value);
    // 0x7100d72364: whether `_30` is set.
    bool sub_7100D72364() const;
    // 0x7100d723dc: `mMode = mode` for modes 0-2.
    void sub_7100D723DC(s32 mode);
    // 0x7100d724f4 / 0x7100d7251c: `_58` and `_58 & mask`.
    u32 sub_7100D724F4() const;
    bool sub_7100D7251C(u32 mask) const;
    // 0x7100d7252c
    Actor* getActor() const;
    // 0x7100d72544: the action code of the resource client (see sub_7100D72534: the attention type).
    AttActionCodeValue sub_7100D72544() const;

private:
    Actor* mActor = nullptr;
    res::AttClientList::Client* mClient = nullptr;
    int _10 = 3;
    int _14 = 0;
    f32 _18 = 0.0;
    f32 _1c = 1.0;
    f32 _20 = 0.0f;
    void* mCallback = nullptr;
    void* _30 = nullptr;
    sead::Buffer<sead::Matrix34f> _38;  // one matrix per check of the resource client
    sead::Vector3f _48;
    u32 _54 = 0;
    u32 _58 = 0;
    int mMode = 0;
    bool mEnabled = true;
    bool _61 = false;
    bool _62 = false;
};

}  // namespace ksys::act
