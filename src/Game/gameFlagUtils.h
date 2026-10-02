#pragma once

#include <prim/seadSafeString.h>

// 0x7100900c48 (CSV name: getFlagInt): reads an int game data flag by name if the game data
// trigger param exists and the value is copied; returns whether it succeeded. The namespace is
// unknown (sibling 0x7100900bb0 / 0x7100900c0c / 0x7100900c84 / 0x7100900ce0 are bool / f32 /
// other variants).
bool getFlagInt(s32* value, const sead::SafeString& flag);
