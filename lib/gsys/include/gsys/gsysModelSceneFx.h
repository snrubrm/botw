#pragma once

#include <basis/seadTypes.h>

namespace gsys {

// The ModelScene effect component at ModelScene +0x3478. Only the create argument is modelled
// so far: ModelSceneFx::initialize 0x7100c2d8b0 takes it by reference and its constructor
// 0x7100c2d624 stores 1 in the first word.
class ModelSceneFx {
public:
    struct CreateArg {
        CreateArg();

        /* 0x0 */ s32 _0;
    };
};

}  // namespace gsys
