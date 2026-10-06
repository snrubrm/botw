#include "Game/AI/aiUnk_71006F5B14.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectChemicalType.h"
#include "KingSystem/Chemical/chmSystemConfig.h"
#include "KingSystem/World/worldManager.h"

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

bool sub_71006F5934(ksys::act::Chemical* chemical) {
    return (chemical->_8 & 2) != 0;
}

void sub_71006F5A80(ksys::act::Chemical* chemical) {
    if (chemical)
        chemical->sub_7100D8F124(ksys::world::Manager::instance()->getElementHolderMaybe());
}

void sub_71006F5AC4(Unk_71006F5DB0 element, ksys::act::Chemical* chemical) {
    if (element == Unk_71006F5DB0::Fire) {
        chemical->sub_7100D90B78();
        chemical->sub_7100D90C2C(true);
    }
    chemical->sub_7100D90AF4(false);
    chemical->_bf |= 2;
}

void sub_71006F5B14(ksys::act::Actor* actor) {
    if (auto* chemicals = actor->getChemicalContainer()) {
        for (s32 i = 0; i < chemicals->_58.size() + chemicals->_80; ++i) {
            auto* chemical = chemicals->sub_7100E37788(i);
            sub_71006F5AC4(sub_71006F5694(actor), chemical);
        }
    }
}

void sub_71006F5BBC(Unk_71006F5DB0 element, ksys::act::Chemical* chemical) {
    if (element == Unk_71006F5DB0::Fire) {
        chemical->sub_7100D90C2C(false);
        chemical->sub_7100D90858(false, 2, false, true, false);
    }
    if (chemical->mMaterial->attribute.ref() & 0x8000)
        chemical->_bf &= ~2;
    if ((chemical->mMaterial->attribute.ref() & 0x108) == 0x108 && !(chemical->_be & 4))
        chemical->sub_7100D90AF4(true);
}

void sub_71006F5C50(ksys::act::Actor* actor) {
    if (auto* chemicals = actor->getChemicalContainer()) {
        for (s32 i = 0; i < chemicals->_58.size() + chemicals->_80; ++i) {
            auto* chemical = chemicals->sub_7100E37788(i);
            sub_71006F5BBC(sub_71006F5694(actor), chemical);
        }
    }
}

bool sub_71006F59C4(ksys::act::Actor* actor, int a2) {
    auto* chemical = a2 < 0 ? actor->getChemicalStuff() : actor->sub_71011D8A34(a2);
    return sub_71006F594C(sub_71006F5694(actor), chemical);
}
