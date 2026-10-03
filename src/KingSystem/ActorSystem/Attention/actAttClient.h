#pragma once

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

private:
    Actor* mActor = nullptr;
    res::AttClientList::Client* mClient = nullptr;
    int _10 = 3;
    int _14 = 0;
    f32 _18 = 0.0;
    f32 _1c = 1.0;
    f32 _20;
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
