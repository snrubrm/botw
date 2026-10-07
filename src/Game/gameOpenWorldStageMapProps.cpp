#include "Game/gameOpenWorldStageMapProps.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking {

bool OpenWorldStageMapProps::getMapFileName(sead::BufferedSafeString* out, int col, int row) {
    out->format("%c-%d/%c-%d", col + 'A', row + 1, col + 'A', row + 1);
    return true;
}

void OpenWorldStageMapProps::getMapSquareFromString(int* col, int* row, const sead::SafeString& name) {
    *col = name[0] - 'A';
    *row = name[2] - '1';
}

void OpenWorldStageMapProps::getMapType(sead::BufferedSafeString* out) {
    out->copy(_1a0);
}

bool OpenWorldStageMapProps::getMapFileNameForPlayerPos(sead::BufferedSafeString* out) {
    ksys::act::Actor* actor = _e0;
    const float x = actor->getMtx().m[0][3];
    const float z = actor->getMtx().m[2][3];
    const int ix = int(x) + 5000;
    int col = ix / 1000;
    const int iz = int(z) + 4000;
    int row = iz / 1000;
    col = sead::Mathi::min(col, 9);
    int c;
    if (ix <= -1000)
        c = 0;
    else
        c = col;
    row = sead::Mathi::min(row, 7);
    int r;
    if (iz <= -1000)
        r = 0;
    else
        r = row;
    return getMapFileName(out, c, r);
}

}  // namespace uking
