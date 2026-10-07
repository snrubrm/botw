#pragma once

#include <prim/seadSafeString.h>

namespace ksys::act {
class Actor;
}

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
    // Parses a square name like "C-4" (name[0] - 'A', name[2] - '1').
    virtual void getMapSquareFromString(int* col, int* row, const sead::SafeString& name);
    // Copies the map type string.
    virtual void getMapType(sead::BufferedSafeString* out);
    // 0x71007c5fb0: calls getMapFileName for the square of the player actor's position.
    virtual bool getMapFileNameForPlayerPos(sead::BufferedSafeString* out);
    // "A-1/A-1": the map file name of the map square (column `col` -> letter, row `row` -> number).
    virtual bool getMapFileName(sead::BufferedSafeString* out, int col, int row);

private:
    u8 _8[0xe0 - 0x8];
    /* 0xe0 */ ksys::act::Actor* _e0;
    u8 _e8[0x1a0 - 0xe8];
    sead::SafeString _1a0;
};

}  // namespace uking
