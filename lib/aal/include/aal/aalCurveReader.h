#pragma once

#include <basis/seadTypes.h>
#include <prim/seadEnum.h>
#include <prim/seadSafeString.h>
#include "aal/aalResourceHeader.h"
#include "aal/aalRollOffCurve.h"
#include "aal/aalUnitDistanceCurve.h"

namespace aal {

/// Reads the binary resource of a CustomCurve (signature "ACTC", version 1): a list of segments.
class CustomCurveReader {
public:
    struct SegmentParam {
        f32 position;
        f32 value;
        /// A CustomCurveType.
        u32 type;
        f32 coefficient;
    };

    explicit CustomCurveReader(const void* data);

    bool isValid() const { return mData != nullptr; }

    s32 getNumOfSegments() const;
    /// nullptr if `index` is out of range.
    const SegmentParam* getSegmentParam(s32 index) const;

private:
    struct Data {
        ResourceHeader header;
        s32 num_segments;
        SegmentParam segments[1];
    };

    const Data* mData = nullptr;
};

/// Reads the binary resource of a RollOffCurve (signature "AROC", versions 1 and 2). The accessors return a default
/// if the resource is not valid.
class RollOffCurveReader {
public:
    explicit RollOffCurveReader(const void* data);

    bool isValid() const { return mData != nullptr; }

    RollOffModel getRollOffModel() const;
    f32 getRefDistance() const;
    f32 getMaxDistance() const;
    f32 getRollOffFactor() const;
    f32 getStartValue() const;
    bool isIncreaseMode() const;
    /// Not stored by version 1 resources (0).
    f32 getCullingStartDistance() const;

private:
    struct Data {
        ResourceHeader header;
        u32 roll_off_model;
        f32 ref_distance;
        f32 max_distance;
        f32 roll_off_factor;
        f32 start_value;
        u32 increase_mode;
        f32 culling_start_distance;
    };

    const Data* mData = nullptr;
    bool mIsVersion1 = false;
};

/// Reads the binary resource of a UnitDistanceCurve (signature "AUDC", version 1).
class UnitDistanceCurveReader {
public:
    explicit UnitDistanceCurveReader(const void* data);

    bool isValid() const { return mData != nullptr; }

    UnitDistanceCurve::CurveType getCurveType() const;
    f32 getStartValue() const;
    f32 getEndValue() const;
    f32 getHoldDistance() const;
    f32 getUnitDistance() const;
    f32 getDecayRatio() const;
    f32 getCullingStartDistance() const;

private:
    struct Data {
        ResourceHeader header;
        u32 curve_type;
        f32 start_value;
        f32 end_value;
        f32 hold_distance;
        f32 unit_distance;
        f32 decay_ratio;
        f32 culling_start_distance;
    };

    const Data* mData = nullptr;
};

/// The list of the assets that loop (signature "BLAL"): the sorted CRC32 hashes of their names. The reader converts the
/// byte order of the list in place.
class LoopAssetListReader {
public:
    explicit LoopAssetListReader(u8* data);

    bool contains(const sead::SafeString& name) const;

private:
    struct Data {
        ResourceHeader header;
        s32 num_hashes;
        u32 hashes[1];
    };

    Data* mData = nullptr;
};

}  // namespace aal
