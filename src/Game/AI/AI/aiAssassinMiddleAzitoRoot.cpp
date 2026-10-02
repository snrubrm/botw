#include "Game/AI/AI/aiAssassinMiddleAzitoRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actUnk_71002dccbc.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Utils/StringUtil.h"

namespace uking::ai {

AssassinMiddleAzitoRoot::AssassinMiddleAzitoRoot(const InitArg& arg) : AssassinNormal(arg) {}

// NON_MATCHING: the original inlines the destructor of the listener _490 (Unk_7102450678), whose
// out-of-line copy is in the listener TU; ours calls it.
AssassinMiddleAzitoRoot::~AssassinMiddleAzitoRoot() = default;

bool AssassinMiddleAzitoRoot::init_(sead::Heap* heap) {
    if (!AssassinNormal::init_(heap))
        return false;
    _568 = false;
    return true;
}

void AssassinMiddleAzitoRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    AssassinNormal::enter_(params);
}

void AssassinMiddleAzitoRoot::leave_() {
    AssassinNormal::leave_();
}

void AssassinMiddleAzitoRoot::loadParams_() {
    AssassinNormal::loadParams_();
    getStaticParam(&mEntryPoint_s, "EntryPoint");
    getStaticParam(&mDemoName_s, "DemoName");
    getStaticParam(&mLikeItem_s, "LikeItem");
}

// NON_MATCHING: block layout of the Enemy cast check (the original re-tests the cast result with a csel
// and keeps the ActorFlag2 test as a 32-bit load)
void AssassinMiddleAzitoRoot::calc_() {
    getCurrentChild();

    if (!isCurrentChild("プレイヤー発見")) {
        _568 = false;
    } else if (!_568) {
        auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
        if (enemy != nullptr &&
            mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_2000000) &&
            enemy->_e84.isOnBit(9)) {
            _568 = sub_710031E748(nullptr);
        }
    }

    if (getCurrentChild()->isFailed() &&
        (isCurrentChild("不審物発見") || isCurrentChild("好物発見"))) {
        sub_710031EAD0(&_400);
    }

    AssassinNormal::calc_();
}

void AssassinMiddleAzitoRoot::m49(Unk1* out, s32 idx) {
    auto* weapons = mActor->getWeapons();
    if (weapons && !weapons->mWeapons[0]._10) {
        switch (m52(idx)) {
        case 2:
        case 4:
        case 6:
        case 7:
        case 8:
        case 10:
        case 11:
        case 12:
            out->_0 = -1;
            return;
        default:
            break;
        }
    }

    if (isCurrentChild("好物発見")) {
        s32 type = m52(idx);
        switch (type) {
        case 2:
        case 4:
        case 6:
        case 7:
        case 10:
        case 11:
        case 12:
            type = -1;
            break;
        default:
            break;
        }
        out->_0 = type;
        return;
    }

    if (isCurrentChild("プレイヤー発見") &&
        !mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_2000000) &&
        sub_71005D9744(mActor) != 5 && m52(idx) == 8) {
        out->_0 = 8;
        return;
    }

    AssassinNormal::m49(out, idx);
}

s32 AssassinMiddleAzitoRoot::m52(s32 idx) {
    static const s32 sTable[] = {0, 1, 12, 2, 3, 11, 9, 4, 5, 6, 7, 8, 10};
    return sTable[idx];
}

bool AssassinMiddleAzitoRoot::m56(Unk2* out, Unk1* info) {
    if (info->_0 == 12) {
        Unk_71023d8848 filter(&mLikeItem_s);
        return sub_710040CF88(&filter, out);
    }
    return AssassinNormal::m56(out, info);
}

void AssassinMiddleAzitoRoot::m57(s32 type, Unk2* target) {
    if (type == 11 || type == 12) {
        if (!isCurrentChild("音気づき") && !isCurrentChild("諦め") &&
            !isCurrentChild("不審物発見") && !isCurrentChild("不審物排除後") &&
            !isCurrentChild("好物発見")) {
            sub_710040CE58();
        }
        if (type == 11) {
            if (auto* unk = sub_71005D9D68(mActor))
                unk->sub_71002DC628(*target->_0, 0x80);
        }
        _400 = *target->_0;
        return;
    }
    AssassinNormal::m57(type, target);
}

void AssassinMiddleAzitoRoot::m58(s32 type, Unk2* target) {
    if (type == 12) {
        assassinMiddleFindLikeItem(target);
        return;
    }
    AssassinNormal::m58(type, target);
}

void AssassinMiddleAzitoRoot::m59() {
    auto* child = getCurrentChild();
    if (!isCurrentChild("好物発見")) {
        AssassinNormal::m59();
        return;
    }

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_400, &accessor);
    sead::Vector3f pos;
    accessor.getActorMtx().getTranslation(pos);
    child->setDynamicParamImpl(_400, "TargetActor", &ksys::act::ai::ParamPack::setActor);
    child->setDynamicParam(pos, "TargetPos");
}

void AssassinMiddleAzitoRoot::m60(Unk3* out) {
    if (isCurrentChild("好物発見")) {
        out->_0 = 3;
        return;
    }
    AssassinNormal::m60(out);
}

void AssassinMiddleAzitoRoot::m61(Unk3* out) {
    if (isCurrentChild("好物発見")) {
        if (!_400.hasProcInCalcState())
            out->_0 = 3;
        return;
    }
    AssassinNormal::m61(out);
}

// NON_MATCHING: filter construction order, the seal flag test (branches in the original) and
// register allocation
bool AssassinMiddleAzitoRoot::m66(Unk2* out, Unk1* info) {
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return false;
    auto* sensor = awareness->_260[1];
    if (!sensor || sensor->_8.size() == 0)
        return false;

    Unk_71023d8870 filter;
    filter._28 = mActor;
    filter._38 = &_50;
    u8 flags = *mPlayerSoundSealRefCount_a > 0 || _364 > 0.0f;
    if (info->_8 & 0x80)
        flags |= 8;
    if (info->_8 & 0x200)
        flags |= 4;
    if (info->_8 & 0x400)
        flags |= 0x10;
    filter._30 = flags;

    auto* entry = ksys::act::sub_7100D7EEE8(&sensor->_8, &filter);
    if (!entry)
        return false;

    auto* target = sub_71005D9050(mActor);
    if (target && target->hasProc() && *target == entry->mLink)
        return false;
    if (m45(entry->_88, entry->mLink, false))
        return false;
    if (!m44(entry->_88))
        return false;

    auto* unk = sub_71005D9D68(mActor);
    if (!entry->m5(1) && unk && !(info->_8 & 0x800) && unk->sub_71002DC9E8(entry->mLink, 4, false))
        return false;

    out->sub_71003A02A4(entry);
    return true;
}

bool AssassinMiddleAzitoRoot::m67(Unk2* out, Unk1* info) {
    return sub_71003A361C(out, true, info);
}

bool AssassinMiddleAzitoRoot::m76() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;
    return enemy->_e84.isOnBit(9);
}

// NON_MATCHING: the original loads the link buffer pointer once before the loop
bool AssassinMiddleAzitoRoot::sub_710031E748(const char* unit_config_name) {
    _460._18.y(mActor);

    auto* obj = mActor->getMapObject();
    if (!obj)
        return false;
    auto* link_data = obj->getLinkData();
    if (!link_data)
        return false;

    bool found = false;
    for (int i = 0; i < link_data->mObjects.size(); ++i) {
        auto* linked = link_data->mObjects(i);
        if (!linked)
            continue;
        const sead::SafeString name = linked->getUnitConfigName();
        if (unit_config_name && name != unit_config_name)
            continue;
        ksys::act::ActorConstDataAccess accessor;
        linked->getActorWithAccessor(accessor);
        if (accessor.hasProc()) {
            found = true;
            _460.sub_710070DD78(accessor, true);
        }
    }
    return found;
}

// NON_MATCHING: the original tail-calls BaseProcLink::operator=
void AssassinMiddleAzitoRoot::sub_710031EAD0(const ksys::act::BaseProcLink* link) {
    if (!link->hasProcInCalcState())
        return;

    ksys::act::BaseProcLink* entry = nullptr;
    for (auto& l : _4c8) {
        entry = &l;
        if (!l.hasProcInCalcState())
            break;
    }
    *entry = *link;
}

void AssassinMiddleAzitoRoot::assassinMiddleFindLikeItem(Unk2* target) {
    _3ac.reset(8);
    ksys::act::ai::InlineParamPack params;
    params.addActor(*target->_0, "TargetActor", -1);
    params.addVec3(target->_38, "TargetPos", -1);
    changeChild("好物発見", &params);
}

bool AssassinMiddleAzitoRoot::sub_710031F804(const ksys::act::BaseProcLink& link) const {
    for (const auto& l : _4c8) {
        if (l == link)
            return true;
    }
    return false;
}

bool Unk_71023d8870::m2(ksys::act::Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<ksys::act::Unk_71024dc858>(entry);
    if (!target || !target->mLink.hasProcInCalcState())
        return false;
    if (Unk_71024514e8::m2(entry))
        return true;
    if (ksys::act::hasTag(&target->mLink, ksys::act::tags::TypeKokko) && !(_30 & 0x10))
        return !(_30 & 2);
    return false;
}

bool Unk_71023d8848::m2(ksys::act::Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<ksys::act::Unk_71024dc858>(entry);
    if (!target || !target->mLink.hasProcInCalcState())
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&target->mLink, &accessor);
    return ksys::util::sub_71010C2EE4(accessor.getName(), *_28, ',');
}

}  // namespace uking::ai
