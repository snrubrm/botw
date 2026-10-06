#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

namespace gsys {

// The environment (env sets, sky/light parameters) of a ModelScene; it is the sub-object at
// ModelScene + 0x130. It holds an array of data sets (count at 0xb98, pointer at 0xba0, 0x5f0 bytes
// each), and every data set an array of env sets (count at 0x438, pointer at 0x440, 0x1e8 bytes each).
// TODO: incomplete. Only functions that game code calls are declared; the members and the size are
// not modeled yet.
class ModelSceneEnv {
public:
    // 0x7100c2859c (declared only): the index of the enabled env set called `name` in the data set
    // `data_set`, or -1 if there is none. (Descriptive name unknown.)
    int sub_7100C2859C(const sead::SafeString& name, u32 data_set);

    // 0x7100c286ec (declared only): applies the env set `env_set` of the data set `data_set`; with
    // `reset` the current env objects are cleared first.
    void sub_7100C286EC(u32 env_set, bool reset, u32 data_set);
};

}  // namespace gsys
