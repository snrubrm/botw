#pragma once

#include "Game/AI/aiUnk_7102357210.h"

// 0x71005e0420 (CSV name: aiStalPartStuff_2; the name does not fit): the message handler of the
// "item picked up" listener (message 0x8000071) used by NewMannequinRoot, CommonPickedItem and
// EquipStand. Other messages are forwarded to the listener's base handler. `other` defaults to `actor`.
bool handleItemPickedMessageMaybe(const ksys::Message& message, Unk_71023e0020* listener,
                                  ksys::act::Actor* actor, ksys::act::Actor* other);
