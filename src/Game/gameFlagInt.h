#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

/// 0x7100900c48 (CSV name getFlagInt; declared only): reads the integer flag `name` of the game data
/// (TriggerParam::getS32IfCopied on the manager's trigger param; false without a manager).
bool getFlagInt(s32* value, const sead::SafeString& name);
