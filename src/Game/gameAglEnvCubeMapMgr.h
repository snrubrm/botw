#pragma once

#include <basis/seadTypes.h>
#include <container/seadOffsetList.h>
#include <math/seadVector.h>

// Local declaration of the agl::env::CubeMapMgr methods used by Unk_71012a20e0. The class is not
// modelled in lib/agl yet; the four method signatures are the CSV's mangled symbols at 0x7101396a4c
// .. 0x7101398154. Move this into lib/agl when gen adds the class.
namespace agl::env {

class CubeMapMgr {
public:
    class ReservedUnit;

    bool isUnitRenderingFinished(const ReservedUnit* unit) const;
    void setUnitPosition(ReservedUnit* unit, const sead::Vector3f& position);
    void setUnitBufferClear(ReservedUnit* unit, bool clear);
    void pushUpdateRequest(ReservedUnit* unit);

    // Read by the 0x71012a2768 caller: the reserved-unit list at +0x218 (its count at +0x228).
    u8 _0[0x218];
    sead::OffsetList<ReservedUnit> mUnits;
};

}  // namespace agl::env
