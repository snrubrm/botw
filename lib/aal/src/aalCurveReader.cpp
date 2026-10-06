#include "aal/aalCurveReader.h"

namespace aal {

// 0x7100b96984
CustomCurveReader::CustomCurveReader(const void* data) {
    auto* header = static_cast<const Data*>(data);
    if (!header->header.isValid(0x43544341))  // "ACTC"
        return;
    if (header->header.version == 1)
        mData = header;
}

// 0x7100b96a14
s32 CustomCurveReader::getNumOfSegments() const {
    return mData ? mData->num_segments : 0;
}

// 0x7100b96a2c
const CustomCurveReader::SegmentParam* CustomCurveReader::getSegmentParam(s32 index) const {
    if (!mData || index >= mData->num_segments)
        return nullptr;
    return &mData->segments[index];
}

// 0x7100b97368
RollOffCurveReader::RollOffCurveReader(const void* data) {
    auto* header = static_cast<const Data*>(data);
    if (!header->header.isValid(0x434f5241))  // "AROC"
        return;
    if (header->header.version == 2) {
        mData = header;
    } else if (header->header.version == 1) {
        mIsVersion1 = true;
        mData = header;
    }
}

// 0x7100b9740c
RollOffModel RollOffCurveReader::getRollOffModel() const {
    return mData ? RollOffModel(static_cast<int>(mData->roll_off_model)) : RollOffModel();
}

// 0x7100b97424
f32 RollOffCurveReader::getRefDistance() const {
    return mData ? mData->ref_distance : 1.0f;
}

// 0x7100b9743c
f32 RollOffCurveReader::getMaxDistance() const {
    return mData ? mData->max_distance : 0.0f;
}

// 0x7100b97454
f32 RollOffCurveReader::getRollOffFactor() const {
    return mData ? mData->roll_off_factor : 1.0f;
}

// 0x7100b9746c
f32 RollOffCurveReader::getStartValue() const {
    return mData ? mData->start_value : 1.0f;
}

// 0x7100b97484
bool RollOffCurveReader::isIncreaseMode() const {
    return mData ? mData->increase_mode != 0 : false;
}

// 0x7100b974a4
f32 RollOffCurveReader::getCullingStartDistance() const {
    if (!mData)
        return 1.0f;
    if (mIsVersion1)
        return 0.0f;
    return mData->culling_start_distance;
}

// 0x7100b974cc
UnitDistanceCurveReader::UnitDistanceCurveReader(const void* data) {
    auto* header = static_cast<const Data*>(data);
    if (!header->header.isValid(0x43445541))  // "AUDC"
        return;
    if (header->header.version == 1)
        mData = header;
}

// 0x7100b9755c
UnitDistanceCurve::CurveType UnitDistanceCurveReader::getCurveType() const {
    return mData ? UnitDistanceCurve::CurveType(static_cast<int>(mData->curve_type)) : UnitDistanceCurve::CurveType();
}

// 0x7100b97574
f32 UnitDistanceCurveReader::getStartValue() const {
    return mData ? mData->start_value : 1.0f;
}

// 0x7100b9758c
f32 UnitDistanceCurveReader::getEndValue() const {
    return mData ? mData->end_value : 0.0f;
}

// 0x7100b975a4
f32 UnitDistanceCurveReader::getHoldDistance() const {
    return mData ? mData->hold_distance : 0.0f;
}

// 0x7100b975bc
f32 UnitDistanceCurveReader::getUnitDistance() const {
    return mData ? mData->unit_distance : 1.0f;
}

// 0x7100b975d4
f32 UnitDistanceCurveReader::getDecayRatio() const {
    return mData ? mData->decay_ratio : 0.5f;
}

// 0x7100b975ec
f32 UnitDistanceCurveReader::getCullingStartDistance() const {
    return mData ? mData->culling_start_distance : 0.0f;
}

}  // namespace aal
