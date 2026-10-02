#include "Game/AI/AI/aiLandHumGourmandEnemyNormal.h"
#include "Game/AI/aiAwarenessFilters.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actUnk_71002dccbc.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LandHumGourmandEnemyNormal::LandHumGourmandEnemyNormal(const InitArg& arg)
    : LandHumEnemyNormal(arg) {}

LandHumGourmandEnemyNormal::~LandHumGourmandEnemyNormal() = default;

bool LandHumGourmandEnemyNormal::init_(sead::Heap* heap) {
    if (!sead::IsDerivedFrom<act::Enemy>(mActor))
        return false;
    *static_cast<Unk_7102370e70**>(mTargetBaitActorLink_a) = &_440;
    return LandHumEnemyNormal::init_(heap);
}

void LandHumGourmandEnemyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    LandHumEnemyNormal::enter_(params);
    sub_7100472538();
    _418 = ksys::Timer(0, 0);
}

void LandHumGourmandEnemyNormal::calc_() {
    LandHumEnemyNormal::calc_();
}

void LandHumGourmandEnemyNormal::leave_() {
    LandHumEnemyNormal::leave_();
}

void LandHumGourmandEnemyNormal::loadParams_() {
    LandHumEnemyNormal::loadParams_();
    getStaticParam(&mRefindBaitTime_s, "RefindBaitTime");
    getStaticParam(&mEatArea_s, "EatArea");
    getStaticParam(&mEatNavType_s, "EatNavType");
    getAITreeVariable(&mTargetBaitActorLink_a, "TargetBaitActorLink");
    getAITreeVariable(&mIsTrgChangeUnderWaterState_a, "IsTrgChangeUnderWaterState");
}

void LandHumGourmandEnemyNormal::m35() {
    if (*mIsTrgChangeUnderWaterState_a) {
        m36();
        return;
    }
    EnemyNormal::m35();
}

void LandHumGourmandEnemyNormal::m50(Unk1* out, s32 idx) {
    const s32 type = m52(idx);
    if (isCurrentChild("餌発見")) {
        if (type != 11) {
            out->_0 = -1;
            return;
        }
        out->_0 = 11;
        out->_8 |= 0x4000;
        return;
    }

    if (isCurrentChild("見失い")) {
        if (type == 11) {
            out->_0 = 11;
            out->_8 |= 0x2000;
            return;
        }
    } else if (isCurrentChild("音気づき")) {
        if (type == 11) {
            out->_0 = 11;
            out->_8 |= 0x2000;
            return;
        }
    } else if (isCurrentChild("気配気づき")) {
        if (type == 11) {
            out->_0 = 11;
            out->_8 |= 0x2000;
            return;
        }
    } else if (isCurrentChild("攻撃反応")) {
        if (type == 11) {
            out->_0 = 11;
            out->_8 |= 0x2000;
            return;
        }
    } else if (isCurrentChild("浮遊物発見")) {
        if (type == 11) {
            out->_0 = 11;
            out->_8 |= 0x2000;
            return;
        }
    }
    LandHumEnemyNormal::m50(out, idx);
}

s32 LandHumGourmandEnemyNormal::m52(s32 idx) {
    static const s32 sTable[] = {0, 1, 11, 2, 3, 9, 4, 5, 6, 7, 8, 10};
    return sTable[idx];
}

void LandHumGourmandEnemyNormal::sub_7100472538() {
    auto* link =
        sead::DynamicCast<Unk_7102370e70>(*static_cast<Unk_71025afb58**>(mTargetBaitActorLink_a));
    if (!link)
        return;
    auto& bait = link->mLink;
    if (auto* unk = sub_71005D9D68(mActor))
        unk->sub_71002DC8A0(bait, 0x10);
    bait.reset();
}

bool LandHumGourmandEnemyNormal::m56(Unk2* out, Unk1* info) {
    if (info->_0 == 11 && sub_71004729D8(out, info))
        return true;
    return LandHumEnemyNormal::m56(out, info);
}

void LandHumGourmandEnemyNormal::m57(s32 type, Unk2* target) {
    if (type == 11) {
        mActor->getMtx().getTranslation(_424);
        sub_71004727CC(*target->_0);
        return;
    }
    if (type == 10) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(target->_0, &accessor);
        const s32 id = accessor.getBalloonHungActorBaseProcID();
        if (id != -1) {
            if (auto* awareness = mActor->getAwareness()) {
                Unk_7102451768 filter;
                filter._28 = id;
                auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter);
                if (entry) {
                    if (auto* unk = sub_71005D9D68(mActor))
                        unk->sub_71002DC628(entry->_0.mLink, 0x10);
                }
            }
        }
    }
    LandHumEnemyNormal::m57(type, target);
}

void LandHumGourmandEnemyNormal::m58(s32 type, Unk2* target) {
    if (type == 11) {
        sub_71004728A4(target);
        return;
    }
    LandHumEnemyNormal::m58(type, target);
}

void LandHumGourmandEnemyNormal::m59() {
    if (!isCurrentChild("餌発見")) {
        LandHumEnemyNormal::m59();
        return;
    }

    _418.update();
    auto* child = getCurrentChild();
    if (child->isChangeable() && _418.value <= sead::Mathf::epsilon()) {
        auto& bait = sub_7100472AE8();
        if (bait.hasProcInCalcState()) {
            sub_71004727CC(bait);
            child->setDynamicParamImpl(bait, "TargetBait", &ksys::act::ai::ParamPack::setActor);
            const f32 time = *mRefindBaitTime_s;
            _418 = ksys::Timer(time, time);
        } else {
            sub_7100472538();
        }
    }
}

void LandHumGourmandEnemyNormal::m49(Unk1* out, s32 idx) {
    const s32 type = m52(idx);
    if (isCurrentChild("プレイヤー発見")) {
        if (type == 11) {
            out->_0 = -1;
            return;
        }
    } else if (isCurrentChild("攻撃反応")) {
        if (type == 11) {
            out->_0 = -1;
            return;
        }
    } else if (isCurrentChild("見失い")) {
        if (type == 11) {
            out->_0 = -1;
            return;
        }
    } else if (isCurrentChild("脅威感知")) {
        if (type == 11) {
            out->_0 = -1;
            return;
        }
    } else if (isCurrentChild("音気づき")) {
        if (type == 11) {
            auto* bait = sead::DynamicCast<Unk_7102370e70>(
                *static_cast<Unk_71025afb58**>(mTargetBaitActorLink_a));
            if (bait && bait->mLink.hasProcInCalcState()) {
                out->_0 = -1;
                return;
            }
        }
    } else if (isCurrentChild("餌発見")) {
        if (type == 11) {
            out->_0 = -1;
            return;
        }
        if (type <= 3) {
            out->_0 = type;
            return;
        }
        ksys::act::ActorConstDataAccess accessor;
        if (auto* bait = sead::DynamicCast<Unk_7102370e70>(
                *static_cast<Unk_71025afb58**>(mTargetBaitActorLink_a))) {
            ksys::act::acquireActor(&bait->mLink, &accessor);
        }
        if (accessor.sub_71006E3FB4() && type == 10)
            out->_0 = type;
        else
            out->_0 = -1;
        return;
    }
    LandHumEnemyNormal::m49(out, idx);
}

void LandHumGourmandEnemyNormal::m60(Unk3* out) {
    if (isCurrentChild("餌発見")) {
        out->_0 = 1;
        return;
    }
    LandHumEnemyNormal::m60(out);
}

void LandHumGourmandEnemyNormal::m61(Unk3* out) {
    if (isCurrentChild("餌発見")) {
        auto* bait = sead::DynamicCast<Unk_7102370e70>(
            *static_cast<Unk_71025afb58**>(mTargetBaitActorLink_a));
        if (!bait)
            return;
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&bait->mLink, &accessor);
        if (accessor.sub_71006E3FB4())
            out->_0 = 1;
    } else {
        LandHumEnemyNormal::m61(out);
    }
}

bool LandHumGourmandEnemyNormal::sub_71004726B4(ksys::act::BaseProcLink* link) {
    if (m45(mActor->getMtx().getTranslation(), *link, false))
        return true;

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    ksys::act::ActorConstDataAccess parent;
    accessor.acquireConnectedCalcParent(&parent);
    if (!parent.hasProc(mActor) && accessor.sub_7100D10E6C(30))
        return true;
    if (sub_71005DEC08(link, mActor, 999.0f, 999.0f, sead::Mathf::pi()))
        return true;
    if (accessor.sub_71006E3FB4())
        return true;
    return accessor.checkFlag25();
}

void LandHumGourmandEnemyNormal::sub_71004727CC(const ksys::act::BaseProcLink& link) {
    auto* bait =
        sead::DynamicCast<Unk_7102370e70>(*static_cast<Unk_71025afb58**>(mTargetBaitActorLink_a));
    if (!bait || bait->mLink == link)
        return;
    bait->mLink = link;
    if (auto* unk = sub_71005D9D68(mActor))
        unk->sub_71002DC628(link, 0x10);
}

void LandHumGourmandEnemyNormal::sub_71004728A4(Unk2* target) {
    _3ac.reset(8);
    const f32 time = *mRefindBaitTime_s;
    _418 = ksys::Timer(time, time);

    ksys::act::ai::InlineParamPack params;
    params.addActor(*target->_0, "TargetBait", -1);
    params.addBool(!(target->_44 & 4), "IsNotice", -1);
    changeChild("餌発見", &params);
    sub_710039FAA4(target->_38);
}

// NON_MATCHING: the original loads out->_44 before testing the IsNotice bit (the |= 4 paths are
// merged); ours selects with a csel
bool LandHumGourmandEnemyNormal::sub_71004729D8(Unk2* out, Unk1* info) {
    auto* bait =
        sead::DynamicCast<Unk_7102370e70>(*static_cast<Unk_71025afb58**>(mTargetBaitActorLink_a));
    if (bait && !sub_71004726B4(&bait->mLink)) {
        out->sub_710039E308(&bait->mLink);
        out->_44 |= 4;
        return true;
    }

    if (info->_8 & 0x2000)
        return false;
    auto& link = sub_7100472AE8();
    if (!link.hasProcInCalcState())
        return false;
    out->sub_710039E308(&link);
    if (info->_8 & 0x4000)
        out->_44 |= 4;
    else
        out->_44 &= ~4;
    return true;
}

// NON_MATCHING: the original loads mActor for sub_710072E154 before the EatNavType lookup (the lookup
// was inside the argument list) and keeps the awareness loop rotated
ksys::act::BaseProcLink& LandHumGourmandEnemyNormal::sub_7100472AE8() {
    if (!mActor)
        return ksys::act::getDummyBaseProcLink();
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return ksys::act::getDummyBaseProcLink();

    if (auto* unk = sub_71005D9E64(mActor)) {
        sead::Vector3f pos;
        mActor->getMtx().getTranslation(pos);
        auto* link = unk->sub_71002DCEDC(0x100, pos);
        if (link->hasProcInCalcState()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(link, &accessor);
            sead::Vector3f target_pos;
            accessor.getActorMtx().getTranslation(target_pos);
            if ((pos - target_pos).length() <= f32(*mEatArea_s) && !sub_71004726B4(link)) {
                s32 nav_type;
                switch (*mEatNavType_s) {
                case -1:
                    nav_type = -1;
                    break;
                case 0:
                    nav_type = 2;
                    break;
                case 1:
                    nav_type = 13;
                    break;
                case 2:
                    nav_type = 15;
                    break;
                default:
                    nav_type = -1;
                    break;
                }
                if (sub_710072E154(mActor, target_pos, nullptr, nav_type))
                    return *link;
            }
        }
    }

    Unk_7102451380 filter;
    filter._28 = mActor;
    while (auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter)) {
        if (entry->_a8 > f32(*mEatArea_s))
            break;
        if (sub_71004726B4(&entry->_0.mLink))
            continue;
        sead::Vector3f pos;
        entry->_58.getTranslation(pos);
        s32 nav_type;
        switch (*mEatNavType_s) {
        case -1:
            nav_type = -1;
            break;
        case 0:
            nav_type = 2;
            break;
        case 1:
            nav_type = 13;
            break;
        case 2:
            nav_type = 15;
            break;
        default:
            nav_type = -1;
            break;
        }
        if (sub_710072E154(mActor, pos, nullptr, nav_type))
            return entry->_0.mLink;
    }
    return ksys::act::getDummyBaseProcLink();
}

}  // namespace uking::ai
