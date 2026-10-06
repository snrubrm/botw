#include "Game/AI/AI/aiItemConductor.h"
#include "Game/Actor/actArmorBase.h"
#include "Game/gameRuneMgr.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/Effect/eftEffect.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

// 0x71001c2c68 (declared only; an unnamed free function in the ItemConductorDemoBind TU, takes the player).
bool sub_71001C2C68(ksys::act::PlayerBase* player);

namespace uking::ai {

bool ItemConductor::sub_710044EC60() {
    auto* armor = sead::DynamicCast<act::ArmorBase>(mActor);
    if (!armor)
        return false;
    auto* player = sead::DynamicCast<ksys::act::PlayerBase>(armor->getOwner());
    if (!player)
        return false;
    return sub_71001C2C68(player);
}

void ItemConductor::sub_710044F2DC() {
    if (auto* armor = sead::DynamicCast<act::ArmorBase>(mActor)) {
        if (armor->sub_7100E2B948()) {
            sead::Vector3f position_offset;
            sead::Vector3f rotation_offset;
            armor->sub_7100E2B094(&position_offset);
            armor->sub_7100E2B3D0(&rotation_offset);
            getCurrentChild()->setDynamicParam(position_offset, "PosOffset");
            getCurrentChild()->setDynamicParam(rotation_offset, "RotOffsetXyz");
        }
    }
}

bool ItemConductor::sub_710044F408() {
    auto* armor = sead::DynamicCast<act::ArmorBase>(mActor);
    if (!armor)
        return false;
    auto* player = sead::DynamicCast<ksys::act::PlayerBase>(armor->getOwner());
    if (!player)
        return false;
    return player->m287();
}

bool ItemConductor::sub_710044F514() {
    auto* mgr = RuneMgr::instance();
    if (!mgr)
        return false;
    if ((mgr->_94 & 0x20) && (mgr->_90 & 0x10) && mgr->isSelectedRune(3))
        return true;
    if ((mgr->_94 & 0x20) && (mgr->_90 & 0x10) && mgr->isSelectedRune(4))
        return true;
    if ((mgr->_94 & 0x20) && (mgr->_90 & 0x10) && mgr->isSelectedRune(2))
        return true;
    if ((mgr->_94 & 0x20) && (mgr->_90 & 0x10) && mgr->isSelectedRune(6))
        return true;
    if ((mgr->_94 & 0x20) && (mgr->_90 & 0x10))
        return mgr->isSelectedRune(7);
    return false;
}

ItemConductor::ItemConductor(const InitArg& arg)
    : ksys::act::ai::Ai(arg), _38(), _58(), _78() {}

ItemConductor::~ItemConductor() {
    _38.fadeXLink();
    if (_58.sub_7101241B6C())
        _58.fadeXLink();
}

void ItemConductor::calc_() {
    if (getCurrentChild()->isChangeable()) {
        if (isCurrentChild("通常")) {
            sub_710044F2DC();
            if (_58.sub_7101241B6C())
                _58.fadeXLink();
            if (sub_710044EC60()) {
                sub_710044ED64();
                return;
            }
        } else if (isCurrentChild("持たれる")) {
            if (!sub_710044EC60()) {
                sub_710044EF44();
                return;
            }
            if (sub_710044F408()) {
                if (_58.sub_7101241B6C())
                    _58.fadeXLink();
            }
        }
    }
    if (auto* armor = sead::DynamicCast<act::ArmorBase>(mActor)) {
        if (!armor->_8a8) {
            if (ksys::eft::Effect::instance()->hasFlags(ksys::eft::Effect::cFlag_Unk100)) {
                if (!_38.mELink.isActive())
                    xlinkSearchAndEmit(mActor, "Notice", 2, &_38);
            }
            armor->_8a8 = 0xff;
        }
    }
    if (sub_710044F514())
        _78 = true;
}

void ItemConductor::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_710044EC60())
        sub_710044ED64();
    else
        sub_710044EF44();
    _78 = false;
}

void ItemConductor::loadParams_() {}

}  // namespace uking::ai
