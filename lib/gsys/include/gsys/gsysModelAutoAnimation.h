#pragma once

#include <basis/seadTypes.h>
#include <hostio/seadHostIONode.h>

namespace gsys {

class Model;

// Partial layout: the frame rate is consumed by update_(ModelNW*, f32).
class ModelAutoAnimation : public sead::hostio::Node {
private:
    friend class Model;

    u8 _8[0x30 - 8];
    f32 mFrameRate;
};

}  // namespace gsys
