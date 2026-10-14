#pragma once

namespace gsys {
class Model;
}

namespace ksys::act {
class BoneHandle;
}

// Declaration-only helpers of the native 70435C / 70439C bone-handle family.
// NPCGerudoQueenRoot and GerudoQueenBattle supply an array of three BoneHandles.
// Original source owner and namespace are unknown; names remain free placeholders.
void sub_710070435C(ksys::act::BoneHandle* handles);
void sub_710070439C(gsys::Model* model, ksys::act::BoneHandle* handles, bool enabled);
