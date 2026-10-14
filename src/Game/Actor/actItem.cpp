#include "Game/Actor/actItem.h"
#include <basis/seadNew.h>
#include "Game/Actor/Damage/dmgDamageManagerBase.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGlobal.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectItem.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/System/VFR.h"

bool sub_71006E8644(ksys::act::Actor* actor);

namespace uking::act {

Item::Item(const CreateArg& arg) : DynamicActor(arg) {}

ksys::act::BaseProc* Item::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Item(arg);
}

void Item::m63() {
    DynamicActor::m63();
    if (_b98)
        _b98->clear();
}

void Item::initMaybe() {
    DynamicActor::initMaybe();
    _ba9 = false;
    _ba4 = 0;
    _ba8 = true;
    if (ksys::act::getBoolParam(this, "IsDrop", false)) {
        if (auto* global = ksys::act::GlobalParameter::instance()) {
            if (auto* param = global->getGlobalParam())
                _ba4 = param->mDropItemInvincibleTime.ref();
        }
        _ba8 = false;
        if (auto* damage_mgr = getDamageMgr())
            damage_mgr->mField_34 = 1;
    }
    _ba0 = 0;
}

bool Item::shouldUnload(s32* a1) {
    if (ksys::StageInfo::sIsCDungeon)
        return false;
    if (ksys::StageInfo::sIsMainFieldDungeon && ksys::act::hasTag(this, 0xf9c66decu))
        return false;
    if (getParam()->getRes().mGParamList->getItem()->mPlayerUseItem.ref())
        return false;
    return shouldUnloadBecauseOfDistance(a1);
}

bool Item::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    if (!DynamicActor::prepareInit_(heap, arg))
        return false;

    if (sub_71006E8644(this)) {
        _b90 = new (heap, 8) Unk_710244edc0(this);
        if (!_b90)
            return false;
        _b90->m4(heap);
    } else {
        _b90 = nullptr;
    }

    if (getProfile() == "PlayerItem") {
        _b98 = new (heap, 8) Unk_7102357908(this);
        if (!_b98)
            return false;
    } else {
        _b98 = nullptr;
    }
    return true;
}

void Item::preDelete2_(const PreDeleteArg& arg) {
    if (_b90) {
        delete _b90;
        _b90 = nullptr;
    }
    if (_b98) {
        delete _b98;
        _b98 = nullptr;
    }
    DynamicActor::preDelete2_(arg);
}

// NON_MATCHING: the two chase result tests use tbz / cbz swapped (the inlined sead::Mathf::chase).
void Item::calcMaybe() {
    if (!_ba8 && ksys::VFR::chase(&_ba0, _ba4)) {
        _ba8 = true;
        if (auto* damage_mgr = getDamageMgr())
            damage_mgr->mField_34 = 0;
    }
    if (auto* controller = m159())
        controller->sub_71006DFA04(checkFlag(ActorFlag::_25));
    sub_71006DD21C();
    if (_ba9)
        return;
    if (auto* object = getMapObject()) {
        sead::Vector3f pos;
        getMtx().getTranslation(pos);
        sead::Vector3f diff = object->getTranslate() - pos;
        diff.y = 0.0f;
        if (diff.squaredLength() > 0.0025f)
            _ba9 = true;
    }
}

void Item::m79() {
    if (_b98)
        _b98->dispatch();
}

}  // namespace uking::act
