#include "KingSystem/Map/mapMapProperties.h"
#include <prim/seadSafeString.h>

namespace ksys::map {

bool MapProperties::isOpenWorld() {
    return m0() == 0;
}

void MapProperties::getMubinPath(sead::BufferedSafeString* out, int type) {
    sead::FixedSafeString<32> a;
    sead::FixedSafeString<32> b;
    m7(&a, type);
    getSuffix(&b, type);
    out->format("Map/%s/%s/%s.mubin", a.cstr(), b.cstr(), b.cstr());
}

void MapProperties::getSuffix(sead::BufferedSafeString* out, int type) {
    if (type == 0)
        out->copy("_DistanceView");
}

void MapProperties::m7(sead::BufferedSafeString* out, int type) {
    if (type == 0)
        getMapType(out);
}

int MapProperties::m9(int type) {
    return (type == 0) << 1;
}

void MapProperties::getSomeMatrix(sead::Matrix34f* out, int type) {
    if (type == 0)
        *out = sead::Matrix34f::ident;
}

bool MapProperties::m11() {
    return false;
}

}  // namespace ksys::map
