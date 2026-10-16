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

    // Inlined by ksys::gfx::ForestRenderer::requestDraw 0x7100f03964 before setSize: stores the unit
    // pointer array at +0x10 and its length at +0x18. flushUBO reads entry `index` of the array; the
    // pointed-to type (byte count at +0xc) is not identified.
    void setUnits(void** units, u32 num) {
        mUnits = units;
        _18 = num;
    }

private:
    u8 _8[0x10 - 0x8];
    void** mUnits;

public:
    // Upper bound of flushUBO's index in ForestRenderer 0x7100f06904 (meaning unknown).
    u32 _18;

private:
    s32 mSize;
};

}  // namespace gsys
