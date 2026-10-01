#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/Actor/resResourceAttClient.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class Actor;

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
    void setCallback(void* callback);

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
    u32 _38 = 0;
    void* _40 = nullptr;
    sead::Vector3f _48;
    u32 _54 = 0;
    u32 _58 = 0;
    int mMode = 0;
    bool mEnabled = true;
    bool _61 = false;
    bool _62 = false;
};

}  // namespace ksys::act
