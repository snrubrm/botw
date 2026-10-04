#include "Game/AI/aiUnk_71006F5B14.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Chemical/chmSystemConfig.h"

bool sub_71006F594C(Unk_71006F5DB0 element, ksys::act::Chemical* chemical) {
    if (!chemical || !(chemical->_8 & 2))
        return false;
    switch (element.value()) {
    case Unk_71006F5DB0::Ice:
        if ((chemical->mMaterial->attribute.ref() & 0x8000) && !(chemical->_bf & 2))
            return true;
        break;
    case Unk_71006F5DB0::Fire:
        if (chemical->_c0 == 2)
            return true;
        break;
    case Unk_71006F5DB0::Electric:
        if (chemical->_1b8 > 0.0f && !(chemical->_bf & 1))
            return true;
        break;
    default:
        break;
    }
    return false;
}
