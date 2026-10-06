#pragma once

#include <prim/seadSafeString.h>

namespace uking {

// Name from the CSV (OpenWorldStageMapProps::getMapFileName 0x71007c602c, getMapSquareFromString 0x71007c6064,
// getMapType 0x71007c61a0, getMapFileNameForPlayerPos 0x71007c5fb0). The class of these functions is unknown (they
// sit between the OpenWorldStage virtuals and only use `this` for the map type string at 0x1a0); only what the
// matched functions need is declared.
// TODO: layout and virtual functions unknown.
class OpenWorldStageMapProps {
public:
    // "A-1/A-1": the map file name of the map square (column `col` -> letter, row `row` -> number).
    bool getMapFileName(sead::BufferedSafeString* out, int col, int row);
    // Parses a square name like "C-4" (name[0] - 'A', name[2] - '1').
    void getMapSquareFromString(int* col, int* row, const sead::SafeString& name);
    // Copies the map type string.
    void getMapType(sead::BufferedSafeString* out);

private:
    u8 _0[0x1a0];
    sead::SafeString _1a0;
};

}  // namespace uking
