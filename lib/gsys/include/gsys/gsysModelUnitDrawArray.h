#pragma once

#include <basis/seadTypes.h>
#include <hostio/seadHostIONode.h>

namespace gsys {

// TODO
class ModelUnitDrawArray : public sead::hostio::Node {
public:
    struct CreateArg {
        CreateArg();
    };

    ModelUnitDrawArray();
    virtual ~ModelUnitDrawArray();

    // 0x7100c495e8: stores the size at +0x1c.
    void setSize(s32 size);
    // 0x7100c49954. ksys::gfx::ForestRenderer 0x7100f06904 calls it for every index below `_18`.
    void flushUBO(s32 index);

private:
    u8 _8[0x18 - 0x8];

public:
    // Upper bound of flushUBO's index in ForestRenderer 0x7100f06904 (meaning unknown).
    u32 _18;

private:
    s32 mSize;
};

}  // namespace gsys
