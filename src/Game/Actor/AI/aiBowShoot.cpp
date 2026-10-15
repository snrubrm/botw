#include "Game/Actor/AI/aiBowShoot.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/Actor/Damage/dmgInfoManager.h"
#include <prim/seadFormatPrint.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectBow.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ui {
void sub_7100A94AA8(bool value);
}

namespace uking::ai {

// NON_MATCHING: stack layout and the chemical-state branch differ.
void BowShoot::sub_7100339D04() {
    _18c = 0;
    _190 = sub_710033C41C() - 1;
    _180.reset(*mActor->getParam()->getRes().mGParamList->getBow()->mLeadShotInterval);
    _1ba = 0xff;
    auto* bullet = sead::DynamicCast<ksys::act::Bullet>(mActor->getConnectedCalcChild());
    if (bullet) {
        if (auto* chemical = bullet->getChemicalStuff(); chemical && chemical->_c0 == 2)
            _1ba = (chemical->_c & 0x100000) != 0;
    }
    if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor)) {
        _1a0 = *weapon->sub_71002EE46C();
        if (weapon->isParentPlayer()) {
            _194 = *weapon->getAttackPosMaybe();
            weapon->getMtx().getTranslation(_1ac);
        } else {
            weapon->getMtx().getTranslation(_194);
        }
        _1b8 = weapon->_af8._0 == 7;
    }
    sub_710033BF8C(2);
    if (bullet) {
        sub_710033C2C0(bullet->getName(), 1);
        _1b9 = (bullet->_cf4 & 2) != 0;
    }
    sub_710033BDB4("発射");
}

// NON_MATCHING: timer stores are reordered and the repeated chemical-state test is folded.
void BowShoot::sub_7100339F94() {
    _180.reset(*mActor->getParam()->getRes().mGParamList->getBow()->mRapidFireInterval);
    _18c = 0;
    _190 = sub_710033C41C() - 1;
    if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor)) {
        _1a0 = *weapon->sub_71002EE46C();
        if (weapon->isParentPlayer()) {
            _194 = *weapon->getAttackPosMaybe();
            weapon->getMtx().getTranslation(_1ac);
        } else {
            weapon->getMtx().getTranslation(_194);
        }
        _1b8 = weapon->_af8._0 == 7;
    }
    sub_710033BF8C(3);
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(mActor->getConnectedCalcChild())) {
        sub_710033C2C0(bullet->getName(), 1);
        _1b9 = (bullet->_cf4 & 2) != 0;
        if (auto* chemical = bullet->getChemicalStuff(); chemical && chemical->_c0 == 2)
            _1ba = (chemical->_c & 0x100000) != 0;
    }
    sub_710033BDB4("発射");
}

void BowShoot::sub_710033A1F0() {
    if (act::DamageInfoMgr::sub_710067476C()) {
        if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor)) {
            sead::FormatFixedSafeString<64> message("引き絞り度合： %f ", weapon->_d04);
        }
    }
    sub_710033BF8C(1);
    if (auto* actor = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild()))
        sub_710033C2C0(actor->getName(), 1);
    sub_710033BDB4("発射");
}

void BowShoot::sub_710033BDB4(const sead::SafeString& name) {
    if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor)) {
        ksys::act::ai::InlineParamPack params;
        params.addString(weapon->m164(), "NodeName", -1);
        sead::Vector3f rotation;
        weapon->m165(&rotation);
        params.addVec3(rotation, "RotOffset", -1);
        sead::Vector3f translation;
        weapon->m166(&translation);
        params.addVec3(translation, "TransOffset", -1);
        changeChild(name.cstr(), &params);
    }
}

void BowShoot::sub_710033C2C0(const sead::SafeString& arrow_name, s32 count) {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!weapon || !weapon->isParentPlayer() || weapon->bowIsUsedByPlayerAndHasArrowName())
        return;
    auto* current_weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (current_weapon && !current_weapon->bowIsUsedByPlayerAndHasArrowName() &&
        sub_710033C684() < 1)
        return;
    ui::PauseMenuDataMgr::instance()->removeArrow(arrow_name, count);
}

bool BowShoot::sub_710033C888() {
    for (s32 i = 0; i < 20; ++i) {
        if (!mHandles[i].hasProcCreationFailed())
            return false;
    }
    return true;
}

BowShoot::BowShoot(const InitArg& arg) : ksys::act::ai::Ai(arg), mHandles() {}

BowShoot::~BowShoot() {
    for (auto& handle : mHandles)
        handle.deleteProc();
}

void BowShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710033BDB4("リロード");
    _38 = false;
    _1b8 = false;
    _1b9 = false;
    _1ba = 0xff;
    bool arrow_changed = false;
    if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor)) {
        sead::FixedSafeString<32> arrow_name;
        weapon->bowGetArrowName(&arrow_name);
        if (!mArrowName.isEmpty())
            arrow_changed = mArrowName != arrow_name;
    }
    sub_7100338F38(arrow_changed);
}

bool BowShoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() == ksys::MessageType(0x80000c4)) {
        if (_18c == 0) {
            s32 num_ready = 0;
            bool enough = false;
            for (s32 i = 0; i < 20; ++i) {
                if (mHandles[i].isProcReady() && ++num_ready >= _190) {
                    enough = true;
                    break;
                }
            }
            if (!enough && !sub_710033C888())
                return false;
        }
        ui::sub_7100A94AA8(false);
    }
    return false;
}

bool BowShoot::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void BowShoot::leave_() {
    sub_710033BB98();
}

void BowShoot::sub_710033BB98() {
    const s32* life = mActor->getLife();
    if (!life || *life > 0 || !isCurrentChild("発射") || _190 < 1)
        return;
    s32 shot = 0;
    do {
        if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
            weapon && weapon->sub_71002EA0D4()) {
            f32 time = _180.value;
            if (shot != 0)
                time += f32(*mActor->getParam()->getRes().mGParamList->getBow()->mLeadShotInterval * shot);
            sub_710033B16C(time);
        } else if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
                   weapon && weapon->sub_71002EA16C()) {
            f32 time = _180.value;
            if (shot != 0)
                time += f32(*mActor->getParam()->getRes().mGParamList->getBow()->mRapidFireInterval * shot);
            sub_710033AA88(time);
        }
    } while (_18c < _190 && ++shot < _190);
}

s32 BowShoot::sub_710033C41C() {
    s32 count = 0;
    if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
        weapon && weapon->sub_71002EA0D4()) {
        if (auto* current_weapon = sead::DynamicCast<act::Weapon>(mActor))
            count = current_weapon->sub_71002EA124();
        else
            count = 1;
    } else if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
               weapon && weapon->sub_71002EA16C()) {
        if (auto* current_weapon = sead::DynamicCast<act::Weapon>(mActor))
            count = current_weapon->sub_71002EA1A8();
        else
            count = 1;
    }
    if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor)) {
        weapon->isParentPlayer();
        return count < 10 ? count : 10;
    }
    return 0;
}

s32 BowShoot::sub_710033C684() {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!weapon || weapon->bowHasArrowName())
        return 0;
    sead::FixedSafeString<64> name;
    if (weapon->bowGetArrowName(&name))
        return uking::ui::getPorchNum(name);
    return 0;
}

// NON_MATCHING: the natural string comparison and weapon checks differ in instruction scheduling.
bool BowShoot::sub_710033A350() {
    if (!_38) {
        _38 = true;
        return false;
    }
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!weapon || (!weapon->isParentPlayer() &&
                    !weapon->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_200)))
        return false;
    if (isCurrentChild("発射"))
        return false;
    auto* child = sead::DynamicCast<ksys::act::Actor>(weapon->getConnectedCalcChild());
    auto* current_weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!current_weapon || current_weapon->bowIsUsedByPlayerAndHasArrowName() ||
        sub_710033C684() > 0) {
        sead::FixedSafeString<32> arrow_name;
        weapon->bowGetArrowName(&arrow_name);
        sead::SafeString child_name;
        if (child)
            child_name = child->getName();
        else if (_39)
            return false;
        return child_name != arrow_name;
    }
    if (child) {
        weapon->resetConnectedCalcChild(false);
        child->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
    return false;
}

// NON_MATCHING: release-mode branch merging and switch table bounds differ.
void BowShoot::sub_710033BF8C(u8 mode) {
    if (mode == 2 || mode == 3) {
        switch (sub_710033C41C()) {
        case 2:
            xlinkSearchAndEmit(mActor, "Release2", 1, nullptr);
            break;
        case 3:
            xlinkSearchAndEmit(mActor, "Release3", 1, nullptr);
            break;
        case 4:
            break;
        case 5:
            xlinkSearchAndEmit(mActor, "Release5", 1, nullptr);
            break;
        case 1:
        default:
            xlinkSearchAndEmit(mActor, "Release1", 1, nullptr);
            break;
        }
    } else if (mode == 1) {
        xlinkSearchAndEmit(mActor, "Release1", 1, nullptr);
    } else if (mode == 0) {
        xlinkSearchAndEmit(mActor, "ReleaseEmpty", 1, nullptr);
        return;
    }
    auto* actor = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild());
    if (!actor)
        return;
    if (auto* chemicals = actor->getChemicalContainer()) {
        if (auto* element = chemicals->sub_7100E37FA8(0)) {
            if (element->_18->isRigidAttribute6Or14Set(element->_288)) {
                xlinkSearchAndEmit(mActor, "ChemicalShootFire", 1, nullptr);
                return;
            }
        }
    }
    if (auto* chemical = actor->getChemicalStuff()) {
        if (((chemical->mMaterial->attribute.ref() & 0x108) == 0x108 && !(chemical->_be & 4)) ||
            chemical->_1b8 > 0.0f) {
            xlinkSearchAndEmit(mActor, "ChemicalShootElectric", 1, nullptr);
            return;
        }
    }
    if (auto* chemical = actor->getChemicalStuff()) {
        if (chemical->mMaterial->attribute.ref() & 0x8000) {
            xlinkSearchAndEmit(mActor, "ChemicalShootIce", 1, nullptr);
            return;
        }
    }
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(actor); bullet && !(bullet->_cf4 & 2)) {
        if (auto* chemical = actor->getChemicalStuff()) {
            if (chemical->mMaterial->attribute.ref() & 0x10) {
                xlinkSearchAndEmit(mActor, "ChemicalShootBomb", 1, nullptr);
                return;
            }
        }
    }
    if (ksys::act::hasTag(actor, 0x5e27ef10)) {
        xlinkSearchAndEmit(mActor, "ChemicalShootAncient", 1, nullptr);
    } else if (mActor) {
        const auto* params = mActor->getParam()->getRes().mGParamList;
        if (params) {
            const auto* bow = params->getBow();
            if (bow && bow->mArrowName.ref().findIndex("Bright") != -1)
                xlinkSearchAndEmit(mActor, "ChemicalShootBright", 1, nullptr);
        }
    }
}

// NON_MATCHING: handle deletion is unrolled and the retry loop uses indexed array iteration.
void BowShoot::sub_7100338F38(bool clear_handles) {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!weapon || weapon->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_200))
        return;
    if (clear_handles) {
        for (s32 i = 0; i < 20; ++i)
            mHandles[i].deleteProc();
    }
    s32 shot_count;
    auto* rapid = sead::DynamicCast<act::Weapon>(mActor);
    if (rapid && rapid->sub_71002EA0D4()) {
        auto* current = sead::DynamicCast<act::Weapon>(mActor);
        if (!current)
            return;
        shot_count = current->sub_71002EA124();
    } else {
        auto* lead = sead::DynamicCast<act::Weapon>(mActor);
        if (!lead || !lead->sub_71002EA16C())
            return;
        auto* current = sead::DynamicCast<act::Weapon>(mActor);
        if (!current)
            return;
        shot_count = current->sub_71002EA1A8();
    }
    if (shot_count < 2 || !weapon->bowGetArrowName(&mArrowName) || mArrowName == "Empty")
        return;
    ksys::act::InstParamPack pack;
    pack->addPosition(mActor->getMtx().getTranslation());
    pack->addDeleteDistanceSq(999.0f * 999.0f);
    pack->addResourceLane(2);
    for (auto& handle : mHandles) {
        if (!handle.isAllocatedOrFailed() || handle.hasProcCreationFailed()) {
            if (handle.hasProcCreationFailed())
                handle.deleteProcIfFailed();
            ksys::act::ActorCreator::instance()->requestCreateActor(
                mArrowName.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
                &handle, &pack, nullptr, 2);
        }
    }
}

}  // namespace uking::ai
