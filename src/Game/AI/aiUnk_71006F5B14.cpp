#include "Game/AI/aiUnk_71006F5B14.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectChemicalType.h"
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

Unk_71006F5DB0 sub_71006F5694(ksys::act::Actor* actor) {
    Unk_71006F5DB0 element;
    if (auto* chemical_type = actor->getParam()->getRes().mGParamList->getChemicalType()) {
        const sead::SafeString& name = chemical_type->mChemicalType.ref();
        for (int i = 0; i < Unk_71006F5DB0::size(); ++i) {
            if (name.isEqual(Unk_71006F5DB0::text(i))) {
                element = Unk_71006F5DB0(i);
                break;
            }
        }
    }
    return element;
}

void sub_71006F5D3C(Unk_71006F5DB0 element, ksys::act::Actor* actor) {
    if (auto* as_list = actor->getASList()) {
        const sead::SafeString name = element.text();
        as_list->goLimpFromHeadShotMaybe(0x2f, name, 0);
    }
}
