#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

// 0x7100900c48 (CSV name: getFlagInt): reads an int game data flag by name if the game data
// trigger param exists and the value is copied; returns whether it succeeded. The namespace is
// unknown (sibling 0x7100900bb0 / 0x7100900c0c / 0x7100900c84 / 0x7100900ce0 are bool / f32 /
// other variants).
bool getFlagInt(s32* value, const sead::SafeString& flag);

// 0x7100900c0c / 0x7100900ce0 (unnamed in the CSV; names are guesses): the bool / f32 variants of getFlagInt.
bool getFlagBool(bool* value, const sead::SafeString& flag);
bool getFlagF32(f32* value, const sead::SafeString& flag);
// 0x7100900bb0 / 0x7100900c84 (unnamed; the value is read into a local and dropped, the result of the read is
// returned).
bool sub_7100900BB0(const sead::SafeString& flag);
bool sub_7100900C84(const sead::SafeString& flag);
