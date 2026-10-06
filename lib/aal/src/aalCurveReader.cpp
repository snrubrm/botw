#include "aal/aalCurveReader.h"
#include <codec/seadHashCRC32.h>

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

// 0x7100b96bf0
LoopAssetListReader::LoopAssetListReader(u8* data) {
    if (!data)
        return;
    mData = reinterpret_cast<Data*>(data);
    if (mData->header.readSignature() != 0x4c414c42)  // "BLAL"
        return;
    if (sead::Endian::markToEndian(mData->header.byte_order_mark) == sead::Endian::getHostEndian())
        return;

    mData->header.byte_order_mark = sead::Endian::swapU16(mData->header.byte_order_mark);
    mData->num_hashes = sead::Endian::swapU32(mData->num_hashes);
    for (s32 i = 0; i < mData->num_hashes; ++i)
        mData->hashes[i] = sead::Endian::swapU32(mData->hashes[i]);
}

// 0x7100b96d0c
bool LoopAssetListReader::contains(const sead::SafeString& name) const {
    if (!mData || mData->num_hashes < 1)
        return false;

    const u32 hash = sead::HashCRC32::calcStringHash(name);
    u32 low = 0;
    u32 high = mData->num_hashes;
    for (;;) {
        const u32 middle = (low + high) / 2;
        const u32 middle_hash = mData->hashes[middle];
        if (middle_hash == hash)
            return true;
        if (middle_hash < hash) {
            if (low == middle)
                return false;
            low = middle;
        } else {
            if (high == middle)
                return false;
            high = middle;
        }
    }
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
