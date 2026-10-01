#pragma once

#include <hostio/seadHostIONode.h>
#include <math/seadVector.h>
#include <thread/seadCriticalSection.h>

namespace ksys::gfx {

// TODO: incomplete
class ForestRenderer : public sead::hostio::Node {
public:
    virtual ~ForestRenderer();

    s32 x_7(const sead::Vector3f& vec);
    bool x_9();

    sead::CriticalSection mCS;
    u64 _48;
    u32 _50;
    s32 _54;
};

}  // namespace ksys::gfx
