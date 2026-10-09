#pragma once

#include <container/seadOffsetList.h>
#include "aal/aalCustomCurve.h"

namespace aal {

// Constructor ba8cac establishes validity at8 and the OffsetList at10,
// using CustomCurveSegment node offset10. Independent full caller ba3b30
// reserves exactly0x28 bytes, copies all four accessor values into actual
// CustomCurveSegment objects and explicitly invokes this reader's D2.
// Native table24c59e0 contains this concrete class's own D1/D0 only.
// No base interface or base destructor is introduced or changed.
class CustomCurveXmlReader {
public:
    CustomCurveXmlReader(const sead::SafeString& category, const sead::SafeString& path,
                         sead::Heap* heap);
    virtual ~CustomCurveXmlReader();

    f32 getSegmentPos(s32 index) const;
    f32 getSegmentValue(s32 index) const;
    CustomCurveType getSegmentType(s32 index) const;
    f32 getSegmentCoef(s32 index) const;

private:
    bool loadSettingByXml_(const sead::SafeString& category, const sead::SafeString& path,
                           sead::Heap* heap);
    bool mValid = false;
    sead::OffsetList<CustomCurveSegment> mSegments;
};
static_assert(sizeof(CustomCurveXmlReader) == 0x28);

}  // namespace aal
