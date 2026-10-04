#include "Game/AI/aiUnk_71006F5B14.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Chemical/chmSystemConfig.h"

// NON_MATCHING: the original compares the element without the SEAD_ENUM stack round trip (switch on a SEAD_ENUM adds it)
bool sub_71006F594C(Unk_71006F5DB0 element, ksys::act::Chemical* chemical) {
    if (!chemical || !(chemical->_8 & 2))
        return false;
    switch (int(element)) {
    case Unk_71006F5DB0::Fire:
        return chemical->_c0 == 2;
    case Unk_71006F5DB0::Electric:
        return chemical->_1b8 > 0.0f && !(chemical->_bf & 1);
    case Unk_71006F5DB0::Ice:
        return (chemical->mMaterial->attribute.ref() & 0x8000) && !(chemical->_bf & 2);
    default:
        return false;
    }
}
