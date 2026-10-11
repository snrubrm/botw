#pragma once

#include <prim/seadEnum.h>

namespace aal {

class AttenuationXml {
public:
    // Native enum text tables preserve the spaces surrounding each comma.
    SEAD_ENUM(CustomCurveSegmentElmType, Pos , Value , Type , Coef)
    SEAD_ENUM(RollOffCurveElmType, RollOffModel , RefDistance , MaxDistance , RollOffFactor , StartValue , IsIncreaseMode , CullingStartDistance)
    SEAD_ENUM(UnitDistanceCurveElmType, CurveType , StartValue , EndValue , HoldDistance , UnitDistance , DecayRatio , CullingStartDistance)
};

}  // namespace aal
