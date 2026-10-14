#include "Game/Actor/AI/aiItemConductor.h"
#include "Game/Actor/actArmorBase.h"
#include "Game/gameRuneMgr.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/Effect/eftEffect.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

// 0x71001c2c68 (declared only; an unnamed free function in the ItemConductorDemoBind TU, takes the player).
bool sub_71001C2C68(uking::act::PlayerBase* player);

namespace uking::ai {

// NON_MATCHING: shared effect emission schedules argument setup after the rune branches.
void ItemConductor::runeEmitItemEffect() {
    const char* effect;
    if (!RuneMgr::instance())
        return;
    if (RuneMgr::instance()->isSelectedRune(3)) {
        effect = "Item_BitaLock";
    } else {
        if (!RuneMgr::instance())
            return;
        if (RuneMgr::instance()->isSelectedRune(4)) {
            effect = "Item_IceMaker";
        } else {
            if (!RuneMgr::instance())
                return;
            if (RuneMgr::instance()->isSelectedRune(2)) {
                effect = "Item_Magne";
            } else {
                if (!RuneMgr::instance())
                    return;
                if (RuneMgr::instance()->isSelectedRune(7)) {
                    effect = "Item_Amiibo";
                } else {
                    if (!RuneMgr::instance() || !RuneMgr::instance()->isSelectedRune(6))
                        return;
                    effect = "Item_Bike";
                }
            }
        }
    }
    xlinkSearchAndEmit(mActor, effect, 2, &_58);
}

void ItemConductor::sub_710044EF44() {
    sead::SafeString bone_name;
    sead::Vector3f pos_offset;
    sead::Vector3f rot_offset;
    if (auto* armor = sead::DynamicCast<act::ArmorBase>(mActor)) {
        bone_name = armor->sub_7100E2AEF4();
        armor->sub_7100E2B094(&pos_offset);
        armor->sub_7100E2B3D0(&rot_offset);
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addString(bone_name, "BoneName", -1);
    pack.addVec3(pos_offset, "PosOffset", -1);
    pack.addVec3(rot_offset, "RotOffsetXyz", -1);
    changeChild("通常", &pack);
}

void ItemConductor::sub_710044ED64() {
    if (_78) {
        runeEmitItemEffect();
        _78 = false;
    }
    sead::SafeString bone_name;
    sead::Vector3f pos_offset;
    sead::Vector3f rot_offset;
    if (auto* armor = sead::DynamicCast<act::ArmorBase>(mActor)) {
        bone_name = armor->sub_7100E2AFC4();
        armor->sub_7100E2B718(&pos_offset);
        armor->sub_7100E2B820(&rot_offset);
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addString(bone_name, "BoneName", -1);
    pack.addVec3(pos_offset, "PosOffset", -1);
    pack.addVec3(rot_offset, "RotOffsetXyz", -1);
    changeChild("持たれる", &pack);
}

bool ItemConductor::sub_710044EC60() {
    auto* armor = sead::DynamicCast<act::ArmorBase>(mActor);
    if (!armor)
        return false;
    auto* player = sead::DynamicCast<uking::act::PlayerBase>(armor->getOwner());
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
    auto* player = sead::DynamicCast<uking::act::PlayerBase>(armor->getOwner());
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
