#pragma once

#include <basis/seadTypes.h>

namespace aal {

/// The markers of an asset (see AssetInfo::getMarkerInfo). The memory is owned by the audio meta binary.
class MarkerInfo {
public:
    /// The name of the marker (nullptr if there are no markers).
    const char* getName(s32 index) const;
    s32 getStartPos(s32 index) const;
    /// The record of the marker (nullptr if there are no markers).
    const void* getMetaData(s32 index) const;

    u32 mMarkerNum;
    const void* mMarkers;
    const char* mStringTable;

private:
    struct Marker {
        u32 _0;
        u32 name_offset;
        s32 start_position;
        u32 _c;
    };
};
static_assert(sizeof(MarkerInfo) == 0x18, "aal::MarkerInfo size mismatch");

}  // namespace aal
