#pragma once

#include <math/seadMatrix.h>
#include <utility/aglParameter.h>
#include <utility/aglParameterObj.h>
#include "KingSystem/Utils/Types.h"

namespace gsys {
struct BoneAccessKey;
}

namespace ksys::act {
class Actor;
class ActorConstDataAccess;
}

namespace ksys::res {

struct AttPos {
    AttPos();

    void init(agl::utl::IParameterObj* obj, const char* node_key = "Node",
              const char* offset_key = "Offset", const char* rotate_key = "Rotate",
              const char* y_rot_only_key = "YRotOnly");

    // 0x00000071010952a0
    void edit(sead::Matrix34f* mtx, act::Actor* actor, const gsys::BoneAccessKey* key) const;

    // 0x7101095114 (CSV AttPos::x): when `y_rot_only` is set, rebuilds the basis of `mtx` so that only the rotation
    // about the Y axis is kept.
    void x(sead::Matrix34f* mtx) const;
    // 0x71010954b8 / 0x7101095728 (CSV AttPos::x_1 / x_2): the attention position matrix of an actor (through its
    // data accessor / directly): the bone (or actor) matrix with `x` applied, then the scaled offset and rotation.
    void x_1(sead::Matrix34f* mtx, act::ActorConstDataAccess& accessor) const;
    void x_2(sead::Matrix34f* mtx, act::Actor* actor) const;

    agl::utl::Parameter<sead::SafeString> node;
    agl::utl::Parameter<sead::Vector3f> offset;
    agl::utl::Parameter<sead::Vector3f> rotate;
    agl::utl::Parameter<bool> y_rot_only;
};
KSYS_CHECK_SIZE_NX150(AttPos, 0x98);

}  // namespace ksys::res
