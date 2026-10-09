#pragma once

#include "aal/aalRollOffCurve.h"
#include "aal/aalUnitDistanceCurve.h"

namespace aal {

// Constructor bb3f8c and independent full caller ba52f8 establish these
// fields. The caller reserves 0x28 bytes and explicitly invokes ReaderD2;
// table 24c5b40 contains this concrete class's own D1/D0 only.
class RollOffCurveXmlReader {
public:
    RollOffCurveXmlReader(const sead::SafeString& category, const sead::SafeString& path,
                          sead::Heap* heap);
    virtual ~RollOffCurveXmlReader();

private:
    bool loadSettingByXml_(const sead::SafeString& category, const sead::SafeString& path,
                           sead::Heap* heap);
    bool mValid = false;
    f32 mRefDistance = 1.0f;
    f32 mMaxDistance = 0.0f;
    f32 mRollOffFactor = 1.0f;
    f32 mVolumeScale = 1.0f;
    bool mFlipped = false;
    // Native constructor leaves this field uninitialized; the XML load
    // must supply it before the caller uses the valid reader.
    f32 mCullingStartDistance;
    RollOffModel mModel;
};
static_assert(sizeof(RollOffCurveXmlReader) == 0x28);

// Constructor bb5b38 and independent full caller ba64d0 establish the
// fields and their defaults. The caller reserves 0x28 bytes and explicitly
// invokes ReaderD2; table 24c5bc0 contains this class's own D1/D0 only.
class UnitDistanceCurveXmlReader {
public:
    UnitDistanceCurveXmlReader(const sead::SafeString& category, const sead::SafeString& path,
                               sead::Heap* heap);
    virtual ~UnitDistanceCurveXmlReader();

private:
    bool loadSettingByXml_(const sead::SafeString& category, const sead::SafeString& path,
                           sead::Heap* heap);
    bool mValid = false;
    UnitDistanceCurve::CurveType mCurveType;
    f32 mStartValue = 1.0f;
    f32 mEndValue = 0.0f;
    f32 mHoldDistance = 0.0f;
    f32 mUnitDistance = 1.0f;
    f32 mDecayRatio = 0.5f;
    f32 mCullingStartDistance = 0.0f;
};
static_assert(sizeof(UnitDistanceCurveXmlReader) == 0x28);

}  // namespace aal
