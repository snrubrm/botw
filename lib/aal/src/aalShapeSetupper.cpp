#include "aal/aalShapeSetupper.h"
#include <cstddef>
#include <cstring>
#include "aal/aalShapeMgr.h"
#include "aal/aalShapeTemplate.h"

namespace aal {

// 0x7100b9d3f4
ShapeSetupper::ShapeSetupper(ShapeMgr* shape_mgr) : mShapeMgr(shape_mgr) {}

namespace {
struct ShapeResourceHeader {
    u8 signature[4];
    u16 byte_order;
    u16 version;
    s32 count;
    u32 _c;
};
struct ShapeResourceIndex {
    u32 offset;
    u32 _4;
};
// Versions 1 and 2 share eleven numeric words, followed by two or three flag bytes.
// The zero-terminated name follows those version-specific flag bytes without padding.
struct ShapeResourceRecord {
    u32 values[11];
    u8 flags[3];
};
static_assert(sizeof(ShapeResourceHeader) == 0x10);
static_assert(sizeof(ShapeResourceIndex) == 8);
static_assert(offsetof(ShapeResourceRecord, flags) == 0x2c);
}  // namespace

// NON_MATCHING: native conversions and version branches are separately unrolled.
bool ShapeSetupper::setup(const void* resource, sead::Heap* heap) {
    const auto* bytes = static_cast<const u8*>(resource);
    if (bytes[0] != 'S' || bytes[1] != 'H' || bytes[2] != 'S' || bytes[3] != 'T')
        return false;
    // This native reader accepts only the big-endian mark, including for version 1.
    if (bytes[4] != 0xfe || bytes[5] != 0xff)
        return false;
    ShapeResourceHeader header;
    std::memcpy(&header, bytes, sizeof(header));
    const auto endian = sead::Endian::cBig;
    const u16 version = sead::Endian::toHostU16(endian, header.version);
    if (version == 1) {
        setupOld_(resource, endian, heap);
        return true;
    }
    if (version != 2)
        return false;
    const s32 count = sead::Endian::toHostS32(endian, header.count);
    for (s32 i = 0; i < count; ++i) {
        ShapeResourceIndex index;
        std::memcpy(&index, bytes + sizeof(ShapeResourceHeader) + size_t(i) * sizeof(index),
                    sizeof(index));
        const u32 offset = sead::Endian::toHostU32(endian, index.offset);
        ShapeResourceRecord record;
        std::memcpy(&record, bytes + offset, offsetof(ShapeResourceRecord, flags) + 3);
        ShapeParam param;
        param._0 = sead::Endian::toHostU32(endian, record.values[0]);
        param._4.x = sead::Endian::toHostF32(endian, &record.values[1]);
        param._4.y = sead::Endian::toHostF32(endian, &record.values[2]);
        param._4.z = sead::Endian::toHostF32(endian, &record.values[3]);
        param._10.x = sead::Endian::toHostF32(endian, &record.values[4]);
        param._10.y = sead::Endian::toHostF32(endian, &record.values[5]);
        param._10.z = sead::Endian::toHostF32(endian, &record.values[6]);
        param._1c.x = sead::Endian::toHostF32(endian, &record.values[7]);
        param._1c.y = sead::Endian::toHostF32(endian, &record.values[8]);
        param._1c.z = sead::Endian::toHostF32(endian, &record.values[9]);
        param._28 = sead::Endian::toHostU32(endian, record.values[10]);
        param._2c = record.flags[0] == 1;
        param._2d = record.flags[1] == 1;
        param._2e = record.flags[2] == 1;
        const char* name = reinterpret_cast<const char*>(bytes + offset +
                            offsetof(ShapeResourceRecord, flags) + 3);
        mShapeMgr->createAndRegisterTemplate(name, param, heap);
    }
    return true;
}

// NON_MATCHING: native conversions and local record copies differ.
bool ShapeSetupper::setupOld_(const void* resource, sead::Endian::Types endian, sead::Heap* heap) {
    const auto* bytes = static_cast<const u8*>(resource);
    ShapeResourceHeader header;
    std::memcpy(&header.count, bytes + offsetof(ShapeResourceHeader, count), sizeof(header.count));
    const s32 count = sead::Endian::toHostS32(endian, header.count);
    for (s32 i = 0; i < count; ++i) {
        ShapeResourceIndex index;
        std::memcpy(&index, bytes + sizeof(ShapeResourceHeader) + size_t(i) * sizeof(index),
                    sizeof(index));
        const u32 offset = sead::Endian::toHostU32(endian, index.offset);
        ShapeResourceRecord record;
        std::memcpy(&record, bytes + offset, offsetof(ShapeResourceRecord, flags) + 2);
        ShapeParam param;
        param._0 = sead::Endian::toHostU32(endian, record.values[0]);
        param._4.x = sead::Endian::toHostF32(endian, &record.values[1]);
        param._4.y = sead::Endian::toHostF32(endian, &record.values[2]);
        param._4.z = sead::Endian::toHostF32(endian, &record.values[3]);
        param._10.x = sead::Endian::toHostF32(endian, &record.values[4]);
        param._10.y = sead::Endian::toHostF32(endian, &record.values[5]);
        param._10.z = sead::Endian::toHostF32(endian, &record.values[6]);
        param._1c.x = sead::Endian::toHostF32(endian, &record.values[7]);
        param._1c.y = sead::Endian::toHostF32(endian, &record.values[8]);
        param._1c.z = sead::Endian::toHostF32(endian, &record.values[9]);
        param._28 = sead::Endian::toHostU32(endian, record.values[10]);
        param._2c = record.flags[0] == 1;
        param._2d = record.flags[1] == 1;
        const char* name = reinterpret_cast<const char*>(bytes + offset +
                            offsetof(ShapeResourceRecord, flags) + 2);
        mShapeMgr->createAndRegisterTemplate(name, param, heap);
    }
    return true;
}

}  // namespace aal
