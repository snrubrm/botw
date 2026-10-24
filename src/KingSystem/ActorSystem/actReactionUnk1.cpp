#include "KingSystem/ActorSystem/actReaction.h"
#include <basis/seadNew.h>
#include <prim/seadSafeString.h>
#include <aal/aalHandle.h>
#include <aal/aalSoundSource.h>
#include <aal/aalSpatialSetting.h>
#include <xlink2/xlink2AssetExecutorSLink.h>
#include <xlink2/xlink2EventSLink.h>
#include <xlink2/xlink2Locator.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorX6A0.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actReactionSLinkLimiter.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Physics/physMaterialMask.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldWeatherMgr.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/XLink/xlinkManager.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace ksys::eft {
xlink2::UserInstanceSLink* sub_710105DE68(const char* name, act::Actor* actor, act::Actor* other,
                                          xlink2::Locator* locator);
}

// Original enum ownership and source namespace are unknown; declaration only.
const char* sub_7100E367C0(s32 index);

namespace ksys::act {

namespace {
// 0x71024efe80: the extra labels the reaction XLinks are given by Unk1::init.
const char* const sReactionLabels[] = {
    "Default",        "PlayerHit",     "EnemyHit",       "Guard",     "PlayerGuardJust",
    "EnemyGuardJust", "ArrowHit",      "ArrowDamage",    "HorseStep", "HorseWildStep",
    "Woodcutter",     "Land",          "PlayerFootStep", "TreeSplit", "OreHit",
};

// 0x71024f0290: the water-out asset names, indexed by the water-out kind (0-2).
const char* const sReactionWaterOutNames[] = {
    "ReactionWaterOut",
    "ReactionWaterExit",
    "ReactionWaterOut",
};
}  // namespace

Reaction::Unk1::Unk1() = default;

void Reaction::Unk1::init(sead::Heap* heap) {
    setExtraLabels(_8, sReactionLabels, 15);
    setExtraLabels(_10, sReactionLabels, 15);
    mSLinkLimiter = new (heap, 8) Unk_71024f02a8();
    mSLinkLimiter->init(heap);
    mReactions.init(heap, "GrassTrackLoop");
}

void Reaction::Unk1::sub_7100EC30C4() {
    if (mSLinkLimiter)
        mSLinkLimiter->calc();
    mReactions.calc();
    _108 = 0;
    _10c = 0;
    if (_110 > 0)
        --_110;
    if (_114 > 0)
        --_114;
    if (_118 > 0)
        --_118;
    if (_103)
        --_103;
    _104 = 0;
}

bool Reaction::Unk1::sub_7100EC6DD0(Actor* actor) {
    auto& reactions = mReactions;
    const sead::CoreId core = sead::CoreInfo::getCurrentCoreId();
    return reactions.queue(actor, core);
}

void Reaction::Unk1::sub_7100EC6E30(DamageReactionRequest* request) {
    {
        xlink2::HandleSLink obj_hit_handle;
        sub_7100EC539C(request, &obj_hit_handle, "ObjHit");
    }

    if ((request->_c4 & 1) || ((request->_94 & ~1) == 10))
        return;

    if (StageInfo::sIsFinalTrial && request->_b8) {
        if (request->_b8->getName() == "Priest_Boss_IronBall" &&
            request->mSource.getName() == "PriestBossThunder")
            return;
    }

    xlink2::HandleSLink handle;
    const s32 kind = request->_94;
    sead::FixedSafeString<32> name;
    name.appendWithFormat("Obj%s", kind != 3 ? "Damage" : "Hit");

    const s32 material = int(request->_60.getMaterial());
    switch (material) {
    case phys::Material::Metal:
    case phys::Material::Wood:
    case phys::Material::Bone:
        name.appendWithFormat("_%s", phys::Material::text(material));
        break;
    default:
        name.append("_Metal");
        break;
    }

    if (kind != 3) {
        if (_104 & 2)
            return;
        Actor* actor = request->_b8;
        if (!actor)
            return;
        auto* xlink = actor->getXLink();
        if (!xlink)
            return;
        auto* user = xlink->_50;
        if (!user)
            return;
        const s32 material_78 = int(request->_78.getMaterial());
        const s32 sub_material_idx = request->_78.getSubMaterialIdx();
        const s32 sub_material = xlink::Manager::instance()->getSubMaterialIndex(
            material_78, sub_material_idx);
        user->setPropertyValue(0, material_78);
        user->setPropertyValue(1, sub_material);
        handle = user->searchAndEmit(name.cstr());
        eft::sub_710105E060(&handle, request->mtx);
        _104 |= 2;
    } else {
        if (_104 & 1)
            return;
        sub_7100EC447C(_10, request, &handle, name.cstr());
        _104 |= 1;
    }
}

// NON_MATCHING: same body and instruction order; clang if-converts the water/depth test as branches
// instead of cset+orr, folds the 9/8 list-type select to cinc, and keeps the WaterTrack literal in
// x24 for the fallback comparison (the target derives the fallback from the control flow).
void Reaction::Unk1::sub_7100EC6708(Actor* actor, DamageReactionRequest* request) {
    if (!actor)
        return;

    bool grudge = false;
    if (auto* xlink = actor->getXLink()) {
        if (auto* user = xlink->_50)
            grudge = user->getPropertyValue(0).valueInt == int(phys::Material::GrudgeSlow);
    }

    const bool is_player = isPlayerProfile(actor);

    f32 chemical_value = 0.0f;
    if (is_player) {
        if (auto* chemical = actor->sub_71011D8A44(0)) {
            if (!(chemical->_c & 0x1000000))
                chemical_value = chemical->_190;
        }
    }

    f32 property_value = 0.0f;
    if (auto* xlink = actor->getXLink()) {
        if (auto* user = xlink->_50) {
            const auto* values = user->getPropertyValues();
            if (values)
                property_value = values[7].valueFloat;
        }
    }

    if (property_value > chemical_value)
        chemical_value = property_value;

    if (!(grudge || actor->get68f() || 0.4f <= chemical_value))
        return;

    xlink2::Locator locator;
    const char* name = "WaterTrack";
    if (grudge) {
        name = "WaterTrackGrudge";
    } else if (actor->get68f()) {
        const int material = actor->get6fc();
        if (material == int(phys::Material::GrudgeSlow))
            name = "WaterTrackGrudge";
        else if (material == int(phys::Material::Bog))
            name = "WaterTrackBog";
        else if (material == int(phys::Material::Lava))
            name = "WaterTrackLava";
    }

    auto* user = eft::sub_710105DE68(name, actor, _8, &locator);
    if (!user && name != "WaterTrack")
        user = eft::sub_710105DE68("WaterTrack", actor, _8, &locator);
    if (!user)
        return;

    sead::Vector3f position;
    request->mtx.getTranslation(position);

    const s32 list_type = is_player ? 9 : 8;

    if (mSLinkLimiter) {
        if (!mSLinkLimiter->sub_7100EC9D84(list_type, position, false))
            return;
    }

    xlink2::HandleSLink handle;
    user->emit(locator, &handle);
    if (!handle.isActive())
        return;

    handle.setPosition(position);
    eft::sub_710105E114(&handle, actor);
    if (mSLinkLimiter)
        mSLinkLimiter->sub_7100ECA2A0(list_type, position, handle);
}

// 0x7100ec313c (placeholder name): dispatches a reaction request to the handler of its damage kind.
// NON_MATCHING: four load placements differ (cases 8 and 10 hoist `_8` / `_10` into a callee-saved
// register before the calls in the original). `Actor* actor = _8;` / `= _10;` at the top of those
// two cases reproduces them and makes the row match, but a local used once only to steer a load is
// borderline, so it is not applied.
void Reaction::Unk1::sub_7100EC313C(DamageReactionRequest* request) {
    xlink2::HandleSLink handle;

    if (StageInfo::sIsFinalTrial && request->_98 == 3) {
        if (Actor* actor = request->_b8) {
            if (actor->getName() == "Priest_Boss_ShadowClone")
                return;
        }
    }

    if (request->_c4 & 0x40) {
        if (request->_98 == 3)
            sub_7100EC447C(_10, request, &handle, "ObjHit_Metal");
        else
            sub_7100EC447C(_10, request, &handle, "EnemyHit_S");
        return;
    }

    switch (request->_90) {
    case 0: {
        const s32 material = int(request->_60.getMaterial());
        const s32 sub_material = request->_60.getSubMaterialIdx();
        auto* manager = xlink::Manager::instance();
        if (manager->getSubMaterialIndex(material, sub_material) !=
            manager->getHolyWallSubMaterialIndex())
            return;
        if (_103)
            return;
        sub_7100EC447C(_10, request, &handle, "HolyWallHit");
        _103 = 5;
        return;
    }
    case 1:
        sub_7100EC4594(request);
        return;
    case 2:
        if (request->_98 != 5)
            sub_7100EC4594(request);
        return;
    case 3:
        sub_7100EC4880(request);
        return;
    case 4:
        sub_7100EC4C00(&handle, request);
        return;
    case 5: {
        xlink2::HandleSLink obj_hit_handle;
        if (request->_b8) {
            if (auto* xlink = request->_b8->getXLink()) {
                if (auto* user = xlink->_50) {
                    user->searchAndEmit(sub_7100E367C0(5), &obj_hit_handle);
                    if (obj_hit_handle.isActive())
                        return;
                }
            }
        }
        sub_7100EC447C(_10, request, &obj_hit_handle, sub_7100E367C0(request->_90));
        return;
    }
    case 6:
        if (_114)
            return;
        sub_7100EC447C(_10, request, &handle, sub_7100E367C0(6));
        _114 = 2;
        return;
    case 7:
        if (request->_98 != 1)
            return;
        sub_7100EC447C(_10, request, &handle, sub_7100E367C0(7));
        return;
    case 8: {
        xlink2::HandleSLink ground_handle;
        if (request->mSource.mActor || request->mSource.mLink) {
            sub_7100EC539C(request, &ground_handle, "ReactionEnemyHitGround");
            if (ground_handle.isActive())
                return;
        }
        sub_7100EC447C(_8, request, &ground_handle, "ReactionEnemyHitGround");
        return;
    }
    case 9:
        sub_7100EC513C(request);
        return;
    case 10: {
        const char* name = sub_7100E367C0(10);
        xlink2::HandleSLink ground_handle;
        if (request->mSource.mActor || request->mSource.mLink) {
            sub_7100EC539C(request, &ground_handle, name);
            if (ground_handle.isActive())
                return;
        }
        sub_7100EC447C(_10, request, &ground_handle, name);
        return;
    }
    case 12:
    case 13:
    case 17:
    case 22:
    case 23: {
        if (!_8)
            return;
        auto* xlink = _8->getXLink();
        if (!xlink || !xlink->_50)
            return;
        sub_7100EC6708(request->_b8, request);
        return;
    }
    case 15: {
        if (_102)
            return;
        if (_18) {
            if (auto* xlink = _18->getXLink()) {
                if (auto* user = xlink->_50)
                    user->setPropertyValue(0xe, request->_a0);
            }
        }
        if (_8) {
            if (auto* xlink = _8->getXLink()) {
                if (xlink->_50)
                    sub_7100EC6708(request->_b8, request);
            }
        }
        if (mIsPlayerBarefoot)
            sub_7100EC447C(_18, request, &handle, "PlayerFootStepNaked");
        else
            sub_7100EC447C(_18, request, &handle, sub_7100E367C0(request->_90));
        return;
    }
    case 19: {
        if (_102)
            return;
        if (_18) {
            if (auto* xlink = _18->getXLink()) {
                if (auto* user = xlink->_50)
                    user->setPropertyValue(0xe, request->_a0);
            }
        }
        if (mIsPlayerBarefoot) {
            sead::FixedSafeString<64> name("PlayerLandNaked");
            if (request->_54 > 100.0f)
                name.append("_Large");
            else if (request->_54 > 10.0f)
                name.append("_Normal");
            else
                name.append("_Small");
            if (request->_94 == 0x18)
                name.append("First");
            else
                name.append("Following");
            sub_7100EC447C(_18, request, &handle, name.cstr());
            sub_7100EC5294(request->_b8, request);
            return;
        }
        if (request->_94 == 0x18) {
            if (request->_54 > 100.0f)
                sub_7100EC447C(_18, request, &handle, "FirstLand_Large");
            else if (request->_54 > 10.0f)
                sub_7100EC447C(_18, request, &handle, "FirstLand_Normal");
            else
                sub_7100EC447C(_18, request, &handle, "FirstLand_Small");
        }
        sub_7100EC5294(request->_b8, request);
        return;
    }
    case 20: {
        if (_18) {
            if (auto* xlink = _18->getXLink()) {
                if (auto* user = xlink->_50)
                    user->setPropertyValue(0xe, request->_a0);
            }
        }
        if (mIsPlayerBarefoot)
            sub_7100EC447C(_18, request, &handle, "PlayerLadderStepNaked");
        else
            sub_7100EC447C(_18, request, &handle, "PlayerLadderStep");
        return;
    }
    case 24: {
        sead::FixedSafeString<64> name("PlayerClimb");
        switch (request->_c0) {
        case 1:
            name.append("Weak");
            break;
        case 2:
            name.append("Strong");
            break;
        case 3:
            name.append("Hard");
            break;
        }
        switch (request->_94) {
        case 0xe:
            name.append("FootL");
            break;
        case 0xf:
            name.append("FootR");
            break;
        case 0x1a:
            name.append("HandL");
            break;
        case 0x1b:
            name.append("HandR");
            break;
        }
        sub_7100EC539C(request, &handle, name.cstr());
        return;
    }
    case 27:
    case 28:
        sub_7100EC545C(&handle, request);
        return;
    }
}

// 0x7100ec4c00 (placeholder name): the guard reaction. Emits "Guarded" and the chemical
// hit-additional event for the request source, then "Guard_<material>" for the guarded actor.
void Reaction::Unk1::sub_7100EC4C00(xlink2::HandleSLink* handle, DamageReactionRequest* request) {
    if (request->mSource.mActor || request->mSource.mLink) {
        if (auto* xlink = request->mSource.getXLink()) {
            if (auto* user = xlink->_50) {
                user->searchAndEmit("Guarded", handle);
                xlink2::Locator locator;
                if (user->searchAsset(&locator, "HitAdditional_ChemicalToActor")) {
                    user->setPropertyValue(0x19, 3);
                    user->emit(locator);
                }
            }
        }
        if (handle->isActive())
            return;
    }

    if (!request->_b8)
        return;

    sead::FixedSafeString<19> name("Guard_");
    sead::FixedSafeString<7> material;
    if (request->_60.getMaterial() == phys::Material::Wood)
        material = "Wood";
    else if (request->_60.getMaterial() == phys::Material::Bone)
        material = "Bone";
    else if (request->_60.getMaterial() == phys::Material::Metal)
        material = "Metal";
    else {
        auto* xlink = request->_b8->getXLink();
        if (!xlink || !xlink->_50)
            return;
        xlink->_50->searchAndEmit("Guard", handle);
        return;
    }

    name.append(material);

    auto* xlink = request->_b8->getXLink();
    if (!xlink || !xlink->_50)
        return;
    xlink->_50->searchAndEmit(name.cstr(), handle);
}

// 0x7100ec5294 (placeholder name): the land reaction sound at the request position. On water with
// the "Water_StoneBottom" sub-material the sound is marked as a stone-bottom landing; on GrudgeSlow
// the grudge-slow splash is emitted as well.
void Reaction::Unk1::sub_7100EC5294(Actor* actor, DamageReactionRequest* request) {
    sead::Vector3f position;
    request->mtx.getTranslation(position);

    bool stone_bottom = false;
    if (request->_78.getMaterial() == phys::Material::Water)
        stone_bottom = sead::SafeString(request->_78.getSubMaterialName()) == "Water_StoneBottom";

    sub_7100EC696C(0.5f, actor, position, stone_bottom, true);

    if (request->_78.getMaterial() == phys::Material::GrudgeSlow)
        sub_7100EC5C40(-6.0f, 0.1f, actor, position, 2, 1, &request->_78);
}

// 0x7100ec513c (placeholder name): the weapon-raise shock reaction; the event name gets the
// material suffix for Metal / Wood / Bone, and otherwise the source actor's name is terminated.
void Reaction::Unk1::sub_7100EC513C(DamageReactionRequest* request) {
    xlink2::HandleSLink handle;
    sub_7100EC539C(request, &handle, "WeaponRaiseShock");
    if (handle.isActive())
        return;

    sead::FixedSafeString<32> name;
    name.format("WeaponRaiseShock");

    const s32 material = int(request->_60.getMaterial());
    switch (material) {
    case phys::Material::Metal:
    case phys::Material::Wood:
    case phys::Material::Bone:
        name.appendWithFormat("_%s", phys::Material::text(material));
        break;
    default:
        if (auto* xlink = request->mSource.getXLink()) {
            if (xlink->mActor)
                xlink->mActor->getName().cstr();
        }
        break;
    }

    sub_7100EC447C(_10, request, &handle, name.cstr());
}

// NON_MATCHING: the blocks and calls are the same, but the original keeps the target kind in a
// stack slot (stur / ldur) while ours holds it in x22; that also costs one extra callee-saved
// register and 0x10 more frame.
// 0x7100ec4880 (placeholder name): the hit reaction. The target kind (5 when both the target and
// the reaction kind are 3) selects the event name; the SpHit / chemical hit-additional events and
// the BreakByReaction event follow for the kinds that request them.
void Reaction::Unk1::sub_7100EC4880(DamageReactionRequest* request) {
    s32 target_kind = request->_98;
    if (target_kind == 3 && request->_94 == 3)
        target_kind = 5;

    switch (target_kind) {
    case 1: {
        xlink2::HandleSLink handle;
        if (request->mSource.mActor || request->mSource.mLink) {
            sub_7100EC539C(request, &handle, "PlayerHit");
            if (handle.isActive())
                break;
        }
        sub_7100EC447C(_10, request, &handle, "PlayerHit");
        break;
    }
    case 3:
    case 4:
    case 9: {
        {
            xlink2::HandleSLink handle;
            if (request->mSource.mActor || request->mSource.mLink) {
                sub_7100EC539C(request, &handle, "ArrowHit");
                if (!handle.isActive())
                    sub_7100EC447C(_10, request, &handle, "ArrowHit");
            } else {
                sub_7100EC447C(_10, request, &handle, "ArrowHit");
            }
        }
        if ((request->_a4 & ~1) != 2)
            break;
        {
            xlink2::HandleSLink handle;
            if (request->mSource.mActor || request->mSource.mLink) {
                sub_7100EC539C(request, &handle, "HitAdditional_SpHit");
                if (handle.isActive())
                    break;
            }
            sub_7100EC447C(_10, request, &handle, "HitAdditional_SpHit");
        }
        break;
    }
    case 5:
    case 6:
    case 8: {
        xlink2::HandleSLink handle;
        {
            const s32 material = int(request->_60.getMaterial());
            const s32 sub_material = request->_60.getSubMaterialIdx();
            auto* manager = xlink::Manager::instance();
            if (manager->getSubMaterialIndex(material, sub_material) ==
                manager->getHolyWallSubMaterialIndex()) {
                if (_103)
                    break;
                sub_7100EC447C(_10, request, &handle, "HolyWallHit");
                _103 = 5;
                break;
            }
        }
        if (request->_c4 & 1)
            break;
        if ((request->_94 & ~1) == 10)
            break;

        if (int(request->_60.getMaterial()) == 0x20) {
            sub_7100EC539C(request, &handle, "ArrowBarrierHit");
        } else if (sub_7100EE19C0(request->_78) && !sub_7100EE1B34(request->_78)) {
            sub_7100EC539C(request, &handle, "ArrowGroundBounce");
        } else {
            sub_7100EC539C(request, &handle, "ArrowGroundHit");
        }

        if (request->_c4 & 1) {
            if (auto* actor = request->_b8) {
                if (auto* xlink = actor->getXLink()) {
                    if (xlink->_cc.isOn(0x200000)) {
                        if (auto* user = xlink->_50) {
                            auto break_handle = user->searchAndEmit("BreakByReaction");
                            eft::sub_710105E060(&break_handle, request->mtx);
                        }
                    }
                }
            }
        }
        break;
    }
    case 7: {
        xlink2::HandleSLink handle;
        if (request->mSource.mActor || request->mSource.mLink) {
            sub_7100EC539C(request, &handle, "ArrowWaterHit");
            if (handle.isActive())
                break;
        }
        sub_7100EC447C(_10, request, &handle, "ArrowWaterHit");
        break;
    }
    }

    if (target_kind != 2 && target_kind != 7) {
        xlink2::HandleSLink handle;
        if (target_kind == 6)
            sub_7100EC539C(request, &handle, "HitAdditional_ChemicalToGround");
        else
            sub_7100EC539C(request, &handle, "HitAdditional_ChemicalToActor");
    }
}

// NON_MATCHING: the body is the same, but the original keeps the target kind in a stack slot
// (str / ldr around the two adjustments) while ours if-converts them into a register, and it keeps
// the per-kind mask in x22 across the calls; 8 instructions differ.
// 0x7100ec4594 (placeholder name): the player / enemy hit reaction. The target kind 4 counts as 3
// unless request bit 4 is set; the EnemyHit branch records a per-kind emitted bit and also emits the
// SpHit event, and kinds 5 / 8 emit the object-hit reaction and the BreakByReaction event.
void Reaction::Unk1::sub_7100EC4594(DamageReactionRequest* request) {
    s32 kind = request->_98;
    if (kind == 4 && !(request->_c4 & 0x10))
        kind = 3;
    else if (kind == 3 && request->_94 == 3)
        kind = 5;

    switch (kind) {
    case 1: {
        xlink2::HandleSLink handle;
        if (request->mSource.mActor || request->mSource.mLink) {
            sub_7100EC539C(request, &handle, "PlayerHit");
            if (!handle.isActive())
                sub_7100EC447C(_10, request, &handle, "PlayerHit");
        } else {
            sub_7100EC447C(_10, request, &handle, "PlayerHit");
        }
        break;
    }
    case 3: {
        const s32 flag = (request->_94 == 8 || request->_94 == 5) ? 3 : 2;
        const u8 mask = u8(1 << flag);
        if (!(_104 & mask)) {
            {
                xlink2::HandleSLink handle;
                if (request->mSource.mActor || request->mSource.mLink) {
                    sub_7100EC539C(request, &handle, "EnemyHit");
                    if (!handle.isActive())
                        sub_7100EC447C(_10, request, &handle, "EnemyHit");
                } else {
                    sub_7100EC447C(_10, request, &handle, "EnemyHit");
                }
            }
            if ((request->_a4 & ~1) == 2) {
                xlink2::HandleSLink handle;
                if (request->mSource.mActor || request->mSource.mLink) {
                    sub_7100EC539C(request, &handle, "HitAdditional_SpHit");
                    if (!handle.isActive())
                        sub_7100EC447C(_10, request, &handle, "HitAdditional_SpHit");
                } else {
                    sub_7100EC447C(_10, request, &handle, "HitAdditional_SpHit");
                }
            }
        }
        _104 |= mask;
        break;
    }
    case 5:
    case 8: {
        sub_7100EC6E30(request);
        if (request->_c4 & 1) {
            if (auto* actor = request->_b8) {
                if (auto* xlink = actor->getXLink()) {
                    if (xlink->_cc.isOn(0x200000)) {
                        if (auto* user = xlink->_50) {
                            auto break_handle = user->searchAndEmit("BreakByReaction");
                            eft::sub_710105E060(&break_handle, request->mtx);
                        }
                    }
                }
            }
        }
        break;
    }
    case 9: {
        xlink2::HandleSLink handle;
        if (request->mSource.mActor || request->mSource.mLink) {
            sub_7100EC539C(request, &handle, "EnemyHit");
            if (!handle.isActive())
                sub_7100EC447C(_10, request, &handle, "EnemyHit");
        } else {
            sub_7100EC447C(_10, request, &handle, "EnemyHit");
        }
        sub_7100EC6E30(request);
        break;
    }
    }
}

// NON_MATCHING: the original tests the property array pointer at user+0x70 against -20
// (cmn x8, #0x14); the natural property-value check also loads the value.
// 0x7100ec696c: emits the puddle-hit reaction for `actor` and writes the hit position into the
// event. The actor's own SLink user is used when it has the asset; otherwise the reaction falls
// back to the second actor's user. Property 7 is 1.0 for stone bottoms and the weather wetness
// otherwise.
bool Reaction::Unk1::sub_7100EC696C(f32 speed, Actor* actor, const sead::Vector3f& position,
                                    bool stone_bottom, bool flag) {
    if (!actor)
        return false;
    auto* reaction = Reaction::instance();
    if (!reaction)
        return false;
    if (actor->get4f8() > 0.0f)
        return false;
    if (!flag)
        return false;

    f32 wetness;
    auto* xlink = actor->getXLink();
    if (xlink && xlink->_50 && xlink->_50->getPropertyValue(0).valueInt != -20) {
        if (!stone_bottom)
            return false;
        wetness = 1.0f;
    } else if (stone_bottom) {
        wetness = 1.0f;
    } else {
        if (actor->_6a0->_10._8 & 8)
            return false;
        wetness = world::Manager::instance()->getWeatherMgrUnchecked()->mTransition._2d0;
        if (wetness < 0.1f)
            return false;
    }

    const s32 is_player = isPlayerProfile(actor);
    if (mSLinkLimiter) {
        s32 list_type = 6;
        if (is_player)
            list_type = 7;
        if (!mSLinkLimiter->sub_7100EC9D84(list_type, position, false))
            return false;
    }

    xlink2::HandleSLink handle;
    if (auto* xlink = actor->getXLink()) {
        if (auto* user = xlink->_50) {
            user->setPropertyValue(4, speed);
            handle = user->searchAndEmit("ReactionWaterHitPuddle");
        }
    }

    if (!handle.isActive()) {
        auto* xlink = _8->getXLink();
        if (!xlink || !xlink->_50)
            return false;
        auto* user = xlink->_50;
        if (!actor->getPhysicsMainBody())
            return false;
        bool is_long;
        const s32 size = reaction->sub_7100EC2278(actor, &is_long);
        user->setPropertyValue(6, size);
        user->setPropertyValue(4, speed);
        user->setPropertyValue(7, wetness);
        handle = user->searchAndEmit("ReactionWaterHitPuddle");
    }

    if (handle.isActive()) {
        handle.setPosition(position);
        eft::sub_710105E114(&handle, actor);
    }
    if (!handle.isActive())
        return false;
    if (mSLinkLimiter) {
        if (is_player)
            mSLinkLimiter->sub_7100ECA2A0(7, position, handle);
        else
            mSLinkLimiter->sub_7100ECA2A0(6, position, handle);
    }
    return true;
}

// NON_MATCHING: the Locator store order and the SLink Manager instance load are scheduled
// differently (two instruction groups).
// 0x7100ec8c30: the "OutCarryBoxLand" reaction of a carried box that lands. Casts a short ray
// down from the actor, applies the material properties to the SLink user and forwards the hit to
// the puddle reaction and, for GrudgeSlow, the size-scaled reaction.
bool Reaction::Unk1::sub_7100EC8C30(Actor* actor) {
    if (!actor)
        return false;

    xlink2::Locator locator;
    auto* xlink = actor->getXLink();
    if (!xlink)
        return false;
    auto* user = xlink->_50;
    if (!user)
        return false;
    if (!user->searchAsset(&locator, "OutCarryBoxLand"))
        return false;

    phys::RayCastBodyQuery query(nullptr, phys::GroundHit::HitAll);
    query.enableLayer(phys::ContactLayer::EntityGround);
    query.enableLayer(phys::ContactLayer::EntityGroundObject);
    query.enableLayer(phys::ContactLayer::EntityObject);
    query.enableLayer(phys::ContactLayer::EntitySmallObject);
    query.enableLayer(phys::ContactLayer::EntityTree);
    query.enableLayer(phys::ContactLayer::EntityRagdoll);
    query.enableLayer(phys::ContactLayer::EntityNPC);
    query.enableLayer(phys::ContactLayer::EntityPlayer);
    query.setStartAndDisplacement(actor->getMtx().getTranslation(), -sead::Vector3f::ey);
    if (!query.worldRayCast(phys::ContactLayerType::Entity))
        return false;

    if (mSLinkLimiter) {
        if (!mSLinkLimiter->sub_7100EC9D84(0xc, actor->getMtx().getTranslation(), false))
            return false;
    }

    const auto& mask = query.getMaterialMask();
    const s32 material = int(mask.getMaterial());
    user->setPropertyValue(0, material);
    user->setPropertyValue(1, xlink::Manager::instance()->getSubMaterialIndex(
                                  material, mask.getSubMaterialIdx()));
    xlink2::HandleSLink handle;
    user->emit(locator, &handle);
    const bool stone_bottom = mask.getMaterial() == phys::Material::Water &&
        sead::SafeString(mask.getSubMaterialName()) == "Water_StoneBottom";
    sub_7100EC696C(10.0f, actor, actor->getMtx().getTranslation(), stone_bottom, true);
    if (mask.getMaterial() == phys::Material::GrudgeSlow) {
        const u32 size = Reaction::instance()->sub_7100EC2278(actor, nullptr);
        sub_7100EC5C40(10.0f, 0.1f, actor, actor->getMtx().getTranslation(), size, 1, &mask);
    }
    if (mSLinkLimiter)
        mSLinkLimiter->sub_7100ECA2A0(0xc, actor->getMtx().getTranslation(), handle);
    return handle.isActive();
}

// NON_MATCHING: size / material / flag stay in callee-saved registers where the original spills
// them to the stack; that costs two more saved registers and 0x10 more frame.
// 0x7100ec8f78: emits the water footstep asset of the water-out kind `flag` (0-2) for `actor`.
// The event name comes from the actor's own SLink user when it has the asset, otherwise from the
// second actor's user. Property 9 is used for the search-and-emit form and 10 for the emit form;
// the event gets the actor position and the sound source gets the actor positioning.
void Reaction::Unk1::sub_7100EC8F78(f32 speed, Actor* actor, const sead::Vector3f* pos, u64 size,
                                    u64 material, u64 flag) {
    if (!actor)
        return;
    if (actor->get4f8() > 0.0f)
        return;
    if (actor->getActorFlags2().isOn(Actor::ActorFlag2(0x21)))
        return;

    const bool is_player = isPlayerProfile(actor);
    if (!is_player && mSLinkLimiter) {
        if (!mSLinkLimiter->sub_7100EC9D84(4, actor->getMtx().getTranslation(), false))
            return;
    }

    xlink2::Locator locator;
    if (flag > 2)
        return;
    const char* name = sReactionWaterOutNames[flag];

    xlink2::UserInstanceSLink* user = nullptr;
    bool found = false;
    if (auto* xlink = actor->getXLink()) {
        if ((user = xlink->_50))
            found = user->searchAsset(&locator, name);
    }

    if (!_8)
        return;
    if (!found) {
        if (auto* xlink = _8->getXLink())
            user = xlink->_50;
    }
    if (!user)
        return;

    user->setPropertyValue(4, speed);
    user->setPropertyValue(6, s32(size));
    user->setPropertyValue(0, s32(material));

    const f32 value = speed / 30.0f;
    xlink2::HandleSLink handle;
    if (found) {
        user->setPropertyValue(10, value);
        user->emit(locator, &handle);
    } else {
        user->setPropertyValue(9, value);
        user->searchAndEmit(name, &handle);
    }

    if (!handle.isActive())
        return;

    const sead::Vector3f position = actor->getMtx().getTranslation();
    handle.setPosition(position);
    if (auto* executor = static_cast<xlink2::EventSLink*>(handle.getEvent())
                             ->getAliveAssetExecutor()) {
        if (auto* source = executor->getHandle()->getSoundSource())
            source->mSpatialSetting.setActorPositioning(position, sead::Vector3f::ones);
    }
    if (!is_player && mSLinkLimiter)
        mSLinkLimiter->sub_7100ECA2A0(4, position, handle);
}

}  // namespace ksys::act
