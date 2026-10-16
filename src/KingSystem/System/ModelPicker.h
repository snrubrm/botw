#pragma once

#include <heap/seadDisposer.h>
#include <math/seadBoundBox.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace gsys {
class Model;
}

namespace ksys {

namespace act {
class Actor;
}

namespace map {
class Object;
}

// Name from the CSV (createInstance 0x71010b7f9c, init, postCalc, x, x_0, x_1). Singleton (0xc0 bytes) that
// picks an actor, a map object or a named model target. TODO: incomplete (constructor, postCalc and the
// helpers 0x71010b9374 / 0x71010b9568 are not decompiled).
class ModelPicker {
    SEAD_SINGLETON_DISPOSER(ModelPicker)
    ModelPicker();
    ~ModelPicker();

public:
    // Placeholder: the named target copied field by field by x_1.
    struct Target {
        sead::SafeString name;
        u64 _10;
        u32 _18;
        u32 _1c;
        u32 _20;
    };

    // 0x71010b8048
    void init(void* arg);
    // 0x71010b9320 (CSV x): picks an actor.
    void x(act::Actor* actor);
    // 0x71010b9498 (CSV x_0): picks a map object.
    void x_0(map::Object* object);
    // 0x71010b94ec (CSV x_1): picks a named target.
    void x_1(const Target& target);
    // 0x71010b9374 (declared only): updates the highlight of the current pick (false: off).
    void sub_71010B9374(bool on);

private:
    void* _20;
    u64 _28;
    u64 _30;
    u32 _38;
    sead::BoundBox2f _3c;
    u8 _4c[0x78 - 0x4c];
    act::Actor* mActor;
    map::Object* mObject;
    gsys::Model* mModel;
    Target mTarget;
    s32 mState;
};
KSYS_CHECK_SIZE_NX150(ModelPicker, 0xc0);

}  // namespace ksys
