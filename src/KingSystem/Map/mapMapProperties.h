#pragma once

#include <math/seadMatrix.h>
#include <prim/seadSafeString.h>

namespace ksys::map {

// Interface describing the currently loaded map (implemented by StagePreActorCache for open world
// maps and by IndoorStage for indoor stages).
class MapProperties {
public:
    // 0 for open world maps, 1 for indoor stages.
    virtual int m0() = 0;
    virtual void getMapType(sead::BufferedSafeString* out) = 0;
    virtual bool m2(sead::BufferedSafeString* out) = 0;
    virtual bool getMapName(sead::BufferedSafeString* out, int x, int z) = 0;
    virtual void m4(int* x, int* z, const sead::SafeString& name) = 0;
    // 0x00000071007c1c24
    virtual bool isOpenWorld();
    // 0x00000071007c1c48
    virtual void getMubinPath(sead::BufferedSafeString* out, int type);
    // 0x00000071007c1d80
    virtual void m7(sead::BufferedSafeString* out, int type);
    // 0x00000071007c1d94
    virtual void getSuffix(sead::BufferedSafeString* out, int type);
    // 0x00000071007c1e40
    virtual int m9(int type);
    // 0x00000071007c1e50
    virtual void getSomeMatrix(sead::Matrix34f* out, int type);
    // 0x00000071007c1e78
    virtual bool m11();
};

}  // namespace ksys::map
