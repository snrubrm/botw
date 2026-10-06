#include "Game/gameOpenWorldStageMapProps.h"

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

}  // namespace uking
