#pragma once

#include <math/seadVector.h>

#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::map {

class Rail;
class RailConnectablePoint;

// TODO: incomplete
class Placement18 {
public:
    // 0x0000007100d4782c
    ~Placement18();

    // 0x7100d48744 (a stub that tail-calls 0x7100d48254): finds a rail by its unique name
    // (inlined string compare against Rail::getUniqueName; null when there is none). Used by RailMove::enter_.
    Rail* sub_7100D48744(const sead::SafeString& unique_name);
    RailConnectablePoint* sub_7100D488A0(const sead::Vector3f* pos, s32 x, s32 z);
    Rail* sub_7100D48DE0(const sead::SafeString& name, const sead::Vector3f* pos);
    RailConnectablePoint* sub_7100D49000(const sead::Vector3f* pos,
                                       const sead::SafeString& route_id, s32 x, s32 z);
    // Full rail-route scans at 0x7100d49324 and 0x7100d495b0 use SafeString filters.
    // Independent 0x7100eed470 passes both results to the connectable-point rail initializer.
    const RailConnectablePoint* sub_7100D49324(const sead::SafeString& route_ids);
    const RailConnectablePoint* sub_7100D495B0(const sead::SafeString& point_name);

    // 0x7100d48254 (declared only)
    Rail* sub_7100D48254(const sead::SafeString& unique_name);

private:
    void* _0;
    void* _8;
    void* _10;
};
KSYS_CHECK_SIZE_NX150(Placement18, 0x18);

}  // namespace ksys::map
