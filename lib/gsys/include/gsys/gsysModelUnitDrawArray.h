#pragma once

#include <basis/seadTypes.h>
#include <hostio/seadHostIONode.h>

namespace gsys {

class ModelUnit;

// ModelUnit::createDrawArray c3e524 allocates 0x88 bytes, constructs with
// c49050 and retains the result at ModelUnit+28. Destructor c490c8 releases
// the remaining owned arrays, which are not modelled yet.
class ModelUnitDrawArray : public sead::hostio::Node {
public:
    struct CreateArg {
        CreateArg();
        s32 _0;
        u16 _4;
        u16 _6;
    };
    static_assert(sizeof(CreateArg) == 8);

    ModelUnitDrawArray();
    virtual ~ModelUnitDrawArray();

    // 0x7100c495e8: stores the size at +0x1c.
    void setSize(s32 size);
    // 0x7100c4994c reads the same count. Graphics 0x7100f177f4 and the draw-array
    // query 0x710128bbb4 obtain this object through ModelUnit::getDrawArray().
    s32 getSize() const;
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
    // Initialization c49194 stores the owning ModelUnit; setSize uses it.
    ModelUnit* mModelUnit;
    void** mUnits;

public:
    // Upper bound of flushUBO's index in ForestRenderer 0x7100f06904 (meaning unknown).
    u32 _18;

private:
    s32 mSize;
    u8 _20[0x88 - 0x20];
};
static_assert(sizeof(ModelUnitDrawArray) == 0x88);

}  // namespace gsys
