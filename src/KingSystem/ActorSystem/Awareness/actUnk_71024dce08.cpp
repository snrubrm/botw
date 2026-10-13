#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "Game/gameUnkRttiClasses.h"
#include <prim/seadRuntimeTypeInfo.h>

namespace ksys::act {

// 2026-10-07: the sensor clear method calls entry destruction out of line.
bool Unk_71024dce08::m7() { return true; }
void Unk_71024dce08::m8() {}
void Unk_71024dce08::m9() {}
bool Unk_71024dce08::m10() { return false; }
bool Unk_71024dce08::m11() { return true; }
void Unk_71024dce08::m13() {}
sead::BitFlag8* Unk_71024dce08::m16() { return nullptr; }
void Unk_71024dce08::m17() { _8.clear(); }

}  // namespace ksys::act

// vtable 0x71024dcf48 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024dcf48 : public Unk_71024dcf80 {
    SEAD_RTTI_OVERRIDE(Unk_71024dcf48, Unk_71024dcf80)
public:
    ~Unk_71024dcf48() override;
};

// NON_MATCHING: placeholder; the original destructor (0x7100d81f74) also destroys members this class
// does not declare yet.
Unk_71024dcf48::~Unk_71024dcf48() = default;
