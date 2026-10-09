#include "Game/AI/AI/aiBowShoot.h"
#include "Game/Actor/actWeapon.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/Damage/dmgInfoManager.h"
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

void BowShoot::sub_710033A1F0() {
    if (dmg::DamageInfoMgr::sub_710067476C()) {
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
    _1b8 = 0;
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

}  // namespace uking::ai
