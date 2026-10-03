#include "Game/AI/aiUnk_7102450058.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"

Unk_7102450298::Unk_7102450298(ksys::act::Actor* actor) : CarriedData(actor) {}

bool Unk_7102450298::sub_71006F8AB4() const {
    if (!_30)
        return true;
    return !(_30->_50 & 1);
}
