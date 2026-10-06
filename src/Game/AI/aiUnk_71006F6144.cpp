#include "Game/AI/aiUnk_71006F5B14.h"
#include "Game/Actor/actGelEnemy.h"

// Kept in its own TU: the original calls sub_71006F59C4 out of line from here.
void sub_71006F6144(ksys::act::Actor* actor) {
    if (auto* gel = sead::DynamicCast<uking::act::GelEnemy>(actor)) {
        const bool on = sub_71006F59C4(actor, -1);
        gel->_1678 = on ? gel->_1678 | 4 : gel->_1678 & ~4;
    }
}

bool sub_71006F61F0(ksys::act::Actor* actor) {
    if (auto* gel = sead::DynamicCast<uking::act::GelEnemy>(actor))
        return (gel->_1678 & 4) != 0;
    return false;
}
