#pragma once

#include <prim/seadRuntimeTypeInfo.h>

namespace ksys::util {

class TaskData {
    SEAD_RTTI_BASE(TaskData)
public:
    virtual ~TaskData() = default;  // the vtable has D1 / D0 (lane4 s47)
};

}  // namespace ksys::util
