#pragma once

#include <container/seadPtrArray.h>
#include <container/seadTreeMap.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>

#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::map {

class Rail;
class RailPoint;
class RailConnectablePoint;
class RailRoute;
class Unk_7100D49894;

// 0x7100eec698 supplies the route and its SafeString filter; the two route
// scans at 0x7100d49324 inline this same route-id substring test.
bool sub_7100D4953C(const RailRoute* route, const sead::SafeString& route_ids);

// Singleton factory used by Placement18's native construction and destruction.
class Placement18a {
    SEAD_SINGLETON_DISPOSER(Placement18a)
public:
    Placement18a() = default;
};
KSYS_CHECK_SIZE_NX150(Placement18a, 0x20);

class Placement18 {
public:
    // 0x7100d4764c: the second argument is unused by the modelled body (the original passes it).
    Placement18(sead::Heap* heap, void* a);
    // 0x0000007100d4782c
    ~Placement18();

    void sub_7100D48034();
    // 0x7100d47ef4 (CSV Placement18::x; placeholder name): for every rail of the two cell arrays, initializes
    // the junctions of its first and last point.
    void x(sead::Heap* heap);

    // 0x7100d48744 (a stub that tail-calls 0x7100d48254): finds a rail by its unique name
    // (inlined string compare against Rail::getUniqueName; null when there is none). Used by RailMove::enter_.
    Rail* sub_7100D48744(const sead::SafeString& unique_name);
    Rail* sub_7100D48748(s32 cell_idx, u32 rail_type_hash, const u32& hash_id);
    Rail* sub_7100D487BC(s32 cell_idx, u32 rail_type_hash, const u32& hash_id);
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

    void sub_7100D49784(f32* min_dist, const RailPoint** closest, const RailRoute* route,
                         const sead::Vector3f* pos, const sead::SafeString& route_ids);

private:
    // Native outer keys are unsigned hashes; the inner key interface is unresolved.
    using RailTypeMap = sead::TreeMap<u32, Unk_7100D49894*>;
    RailTypeMap* _0;
    sead::PtrArray<sead::PtrArray<Rail>>* _8;
    sead::PtrArray<sead::PtrArray<Rail>>* _10;
};
KSYS_CHECK_SIZE_NX150(Placement18, 0x18);

}  // namespace ksys::map
