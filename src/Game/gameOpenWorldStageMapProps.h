#pragma once

#include <prim/seadSafeString.h>

namespace uking {

// Name from the CSV (OpenWorldStageMapProps::getMapFileName 0x71007c602c, getMapSquareFromString 0x71007c6064,
// getMapType 0x71007c61a0, getMapFileNameForPlayerPos 0x71007c5fb0). These are the open world stage's overrides of
// the ksys::map::MapProperties interface (getMapName / m4 / getMapType; the last one is byte identical to
// StagePreActorCache's, 0x71007c5fb0 is its m2: it calls getMapName for the square of the player's position). The
// OpenWorldStage class itself (Stage + IHandler + MapProperties, `_1a0` = map type string) does not exist yet, so the
// three matched functions live in this placeholder; move them into OpenWorldStage when it is written.
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
