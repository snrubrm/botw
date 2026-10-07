#include "KingSystem/Resource/Actor/resResourceAttCheck.h"
#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/System/CameraMgr.h"
#include "KingSystem/ActorSystem/actUnk_7100e4e084.h"
#include "KingSystem/GameData/gdtManagerInline.h"

namespace ksys::res {

void AttCheck::m4(act::Actor*, sead::Matrix34f*) {}

bool AttCheck::check(act::Actor*, const act::ActorConstDataAccess&, const sead::Matrix34f*,
                     const sead::Vector3f&, const AttCheck_Unk1*, bool, bool) {
    return true;
}

float AttCheck::m6(const act::ActorConstDataAccess&, const sead::Vector3f&) {
    return -1.0;
}

bool AttCheckLine::parse(const CreateArg& arg) {
    mRadius.init(0.0, "Radius", "半径", "Min=0,Max=10", &mObj);
    mAsLineOfSight.init(false, "AsLineOfSight", "視線を透かすコリジョンを無視する", "", &mObj);
    return true;
}

bool AttCheckArea::parse(const CreateArg& arg) {
    mAttPos.init(&mObj);
    mFromPlayer.init(false, "FromPlayer", "目標側基準", "", &mObj);
    return true;
}

void AttCheckArea::m4(act::Actor* actor, sead::Matrix34f* mtx) {
    if (!mFromPlayer.ref())
        mAttPos.x_2(mtx, actor);
}

// NON_MATCHING: register allocation only (the nine products of the local position are the same, the matrix elements
// sit in other s registers)
bool AttCheckArea::check(act::Actor* actor, const act::ActorConstDataAccess& accessor,
                         const sead::Matrix34f* mtx, const sead::Vector3f& pos,
                         const AttCheck_Unk1* arg, bool a6, bool a7) {
    if (arg && arg->_36)
        return true;

    sead::Matrix34f area_mtx;
    const sead::Vector3f* prev_pos;
    if (mFromPlayer.ref()) {
        if (arg)
            area_mtx = arg->_0;
        else
            mAttPos.x_1(&area_mtx, accessor);
        prev_pos = &actor->getPreviousPos();
    } else {
        area_mtx = *mtx;
        prev_pos = &accessor.getPreviousPos();
    }

    sead::Vector3f local;
    area_mtx.getTranslation(local);
    const sead::Vector3f diff = *prev_pos - local;
    local.set(diff.x * area_mtx.m[0][0] + diff.y * area_mtx.m[1][0] + diff.z * area_mtx.m[2][0],
              diff.x * area_mtx.m[0][1] + diff.y * area_mtx.m[1][1] + diff.z * area_mtx.m[2][1],
              diff.x * area_mtx.m[0][2] + diff.y * area_mtx.m[1][2] + diff.z * area_mtx.m[2][2]);

    act::ActorConstDataAccess link(actor);
    return m9(link, local, pos, arg, a6, a7);
}

float AttCheckArea::m6(const act::ActorConstDataAccess& accessor, const sead::Vector3f& scale) {
    return mAttPos.offset.ref().length() + m10(accessor, scale);
}

void AttCheckArea::m7(act::Actor* actor, const act::ActorConstDataAccess& accessor, bool a3) {
    sead::Matrix34f mtx;
    if (mFromPlayer.ref())
        mAttPos.x_1(&mtx, accessor);
    else
        mAttPos.x_2(&mtx, actor);

    act::ActorConstDataAccess link(actor);
    m11(link, mtx, actor->getScale(), a3);
}

bool AttCheckAreaSphere::parse(const CreateArg& arg) {
    mForceEditModelArea.init(false, "ForceEditModelArea", "(モデル範囲)強制編集", "", &mObj);
    mRadius.init(0.0, "Radius", "(モデル範囲)半径", "Min=0.f,Max=100.f", &mObj);
    mFixedRadius.init(-1.0, "FixedRadius", "(アテンション範囲)半径", "Min=-1.f,Max=100.f", &mObj);
    mForceEditMargin.init(false, "ForceEditMargin", "(あそびの範囲)強制編集", "", &mObj);
    mMarginRadius.init(1.0, "MarginRadius", "(あそびの範囲)半径", "Min=0.f,Max=100.f", &mObj);
    return AttCheckArea::parse(arg);
}

bool AttCheckAreaFan::parse(const CreateArg& arg) {
    mAngleCheckIgnoreLockOn.init(false, "AngleCheckIgnoreLockOn", "ロックオン時も角度チェック有効",
                                 "", &mObj);
    mForceEditModelArea.init(false, "ForceEditModelArea", "(モデル範囲)強制編集", "", &mObj);
    mRadius.init(0.0, "Radius", "(モデル範囲)半径", "Min=0.f,Max=100.f", &mObj);
    mTop.init(0.0, "Top", "(モデル範囲)上辺", "Min=-100.f,Max=100.f", &mObj);
    mBottom.init(0.0, "Bottom", "(モデル範囲)下辺", "Min=-100.f,Max=100.f", &mObj);
    mAngle.init(0.0, "Angle", "(アテンション範囲)角度", "Min=0.f,Max=3.1415f", &mObj);
    mFixedRadius.init(-1.0, "FixedRadius", "(アテンション範囲)半径", "Min=-1.f,Max=100.f", &mObj);
    mFixedTop.init(-1.0, "FixedTop", "(アテンション範囲)上辺", "Min=-1.f,Max=100.f", &mObj);
    mFixedBottom.init(-1.0, "FixedBottom", "(アテンション範囲)下辺", "Min=-1.f,Max=100.f", &mObj);
    mForceEditMargin.init(false, "ForceEditMargin", "(あそびの範囲)強制編集", "", &mObj);
    mMarginRadius.init(1.0, "MarginRadius", "(あそびの範囲)半径", "Min=0.f,Max=100.f", &mObj);
    mMarginTop.init(1.0, "MarginTop", "(あそびの範囲)上辺", "Min=0.f,Max=100.f", &mObj);
    mMarginBottom.init(1.0, "MarginBottom", "(あそびの範囲)下辺", "Min=0.f,Max=100.f", &mObj);
    return AttCheckArea::parse(arg);
}

bool AttCheckAreaCylinderFan::parse(const CreateArg& arg) {
    mAngleCheckIgnoreLockOn.init(false, "AngleCheckIgnoreLockOn", "ロックオン時も角度チェック有効",
                                 "", &mObj);
    mForceEditModelArea.init(false, "ForceEditModelArea", "(モデル範囲)強制編集", "", &mObj);
    mRadius.init(0.0, "Radius", "(モデル範囲)半径", "Min=0.f,Max=100.f", &mObj);
    mTop.init(0.0, "Top", "(モデル範囲)上辺", "Min=-100.f,Max=100.f", &mObj);
    mBottom.init(0.0, "Bottom", "(モデル範囲)下辺", "Min=-100.f,Max=100.f", &mObj);
    mAngle.init(0.0, "Angle", "(アテンション範囲)角度", "Min=0.f,Max=3.1415f", &mObj);
    mFixedRadiusCylinder.init(-1.0, "FixedRadiusCylinder", "(アテンション範囲)円柱の半径",
                              "Min=-1.f,Max=100.f", &mObj);
    mFixedRadiusFan.init(-1.0, "FixedRadiusFan", "(アテンション範囲)扇形の半径",
                         "Min=-1.f,Max=100.f", &mObj);
    mFixedTop.init(-1.0, "FixedTop", "(アテンション範囲)上辺", "Min=-1.f,Max=100.f", &mObj);
    mFixedBottom.init(-1.0, "FixedBottom", "(アテンション範囲)下辺", "Min=-1.f,Max=100.f", &mObj);
    mForceEditMargin.init(false, "ForceEditMargin", "(あそびの範囲)強制編集", "", &mObj);
    mMarginRadiusCylinder.init(1.0, "MarginRadiusCylinder", "(あそびの範囲)円柱の半径",
                               "Min=0.f,Max=100.f", &mObj);
    mMarginRadiusFan.init(1.0, "MarginRadiusFan", "(あそびの範囲)扇形の半径", "Min=0.f,Max=100.f",
                          &mObj);
    mMarginTop.init(1.0, "MarginTop", "(あそびの範囲)上辺", "Min=0.f,Max=100.f", &mObj);
    mMarginBottom.init(1.0, "MarginBottom", "(あそびの範囲)下辺", "Min=0.f,Max=100.f", &mObj);
    return AttCheckArea::parse(arg);
}

bool AttCheckAreaBox::parse(const CreateArg& arg) {
    mForceEditModelArea.init(false, "ForceEditModelArea", "(モデル範囲)強制編集", "", &mObj);
    mMin.init(sead::Vector3f::zero, "Min", "(モデル範囲)最小", "Min=-100.f,Max=100.f", &mObj);
    mMax.init(sead::Vector3f::zero, "Max", "(モデル範囲)最大", "Min=-100.f,Max=100.f", &mObj);
    mFixedMin.init(-sead::Vector3f::ones, "FixedMin", "(アテンション範囲)最小",
                   "Min=-1.f,Max=100.f", &mObj);
    mFixedMax.init(-sead::Vector3f::ones, "FixedMax", "(アテンション範囲)最大",
                   "Min=-1.f,Max=100.f", &mObj);
    mForceEditMargin.init(false, "ForceEditMargin", "(あそびの範囲)強制編集", "", &mObj);
    mMarginMin.init(sead::Vector3f::ones, "MarginMin", "(あそびの範囲)最小", "Min=-100.f,Max=100.f",
                    &mObj);
    mMarginMax.init(sead::Vector3f::ones, "MarginMax", "(あそびの範囲)最大", "Min=-100.f,Max=100.f",
                    &mObj);
    return AttCheckArea::parse(arg);
}

AttCheckEachOtherArea::AttCheckEachOtherArea(AttCheckType type) : AttCheck(type) {}

void AttCheckEachOtherArea::m4(act::Actor* actor, sead::Matrix34f* mtx) {
    *mtx = actor->getMtx();
}

bool AttCheckEachOtherArea::parse(const CreateArg& arg) {
    mForceEditModelArea.init(false, "ForceEditModelArea", "(モデル範囲)強制編集", "", &mObj);
    mRadius.init(0.0, "Radius", "(モデル範囲)半径", "Min=0.f,Max=100.f", &mObj);
    mTop.init(0.0, "Top", "(モデル範囲)上辺", "Min=-100.f,Max=100.f", &mObj);
    mBottom.init(0.0, "Bottom", "(モデル範囲)下辺", "Min=-100.f,Max=100.f", &mObj);
    mFixedRadius.init(-1.0, "FixedRadius", "(アテンション範囲)半径", "Min=-1.f,Max=100.f", &mObj);
    mFixedTop.init(-1.0, "FixedTop", "(アテンション範囲)上辺", "Min=-1.f,Max=100.f", &mObj);
    mFixedBottom.init(-1.0, "FixedBottom", "(アテンション範囲)下辺", "Min=-1.f,Max=100.f", &mObj);
    mForceEditMargin.init(false, "ForceEditMargin", "(あそびの範囲)強制編集", "", &mObj);
    mMarginRadius.init(1.0, "MarginRadius", "(あそびの範囲)半径", "Min=0.f,Max=100.f", &mObj);
    mMarginTop.init(1.0, "MarginTop", "(あそびの範囲)上辺", "Min=0.f,Max=100.f", &mObj);
    mMarginBottom.init(1.0, "MarginBottom", "(あそびの範囲)下辺", "Min=0.f,Max=100.f", &mObj);
    mOffsetTop.init(0.0, "OffsetTop", "(アテンションを出される側の範囲オフセット)上辺",
                    "Min=-100,Max=100", &mObj);
    mOffsetBottom.init(0.0, "OffsetBottom", "(アテンションを出される側の範囲オフセット)下辺",
                       "Min=-100,Max=100", &mObj);
    return AttCheck::parse(arg);
}

bool AttCheckLine::check(act::Actor* actor, const act::ActorConstDataAccess& accessor,
                         const sead::Matrix34f*, const sead::Vector3f&, const AttCheck_Unk1*, bool,
                         bool a7) {
    if (a7 && mClient && mClient->getActionCode() == act::AttActionCode::None)
        return true;

    act::ActorConstDataAccess link(actor);
    return act::sub_7100EE3FA8(link, accessor, mAsLineOfSight.ref(), mRadius.ref());
}

bool AttCheckScreen::check(act::Actor* actor, const act::ActorConstDataAccess&,
                           const sead::Matrix34f*, const sead::Vector3f&, const AttCheck_Unk1* arg,
                           bool, bool a7) {
    if ((arg && arg->_35) || a7)
        return true;
    return sub_7100D8C4F8(actor->getPreviousPos());
}

bool AttCheckWeight::check(act::Actor*, const act::ActorConstDataAccess&, const sead::Matrix34f*,
                           const sead::Vector3f&, const AttCheck_Unk1* arg, bool, bool) {
    return arg && arg->_34;
}

bool AttCheckRideSpace::check(act::Actor* actor, const act::ActorConstDataAccess& accessor,
                              const sead::Matrix34f*, const sead::Vector3f&,
                              const AttCheck_Unk1* arg, bool a6, bool) {
    if (!actor)
        return false;
    if (arg)
        return true;

    act::ActorConstDataAccess link(actor);
    auto* horse = link.getHorseRideStuff();

    sead::Vector3f start;
    link.getActorMtx().getTranslation(start);
    start.y += horse ? horse->_38 : 0.0f;

    sead::Vector3f end = start;
    end.y = (a6 ? 0.8f : 0.85f) + end.y;

    phys::RayCastBodyQuery query(accessor.x(0), phys::GroundHit::Player);
    query.enableLayer(phys::ContactLayer::EntityGroundObject);
    query.enableLayer(phys::ContactLayer::EntityGround);
    query.enableLayer(phys::ContactLayer::EntityGroundRough);
    query.enableLayer(phys::ContactLayer::EntityTree);
    query.setStartAndEnd(start, end);
    return !query.worldRayCast(phys::ContactLayerType::Entity);
}

bool AttCheckRideHorse::check(act::Actor*, const act::ActorConstDataAccess&, const sead::Matrix34f*,
                              const sead::Vector3f&, const AttCheck_Unk1*, bool, bool) {
    if (auto* attention = act::Attention::instance())
        return !attention->sub_7100D75430();
    return true;
}

bool AttCheckSwim::check(act::Actor*, const act::ActorConstDataAccess&, const sead::Matrix34f*,
                         const sead::Vector3f&, const AttCheck_Unk1*, bool, bool) {
    if (auto* attention = act::Attention::instance())
        return !attention->sub_7100D75448();
    return true;
}

bool AttCheckCarry::check(act::Actor*, const act::ActorConstDataAccess&, const sead::Matrix34f*,
                          const sead::Vector3f&, const AttCheck_Unk1*, bool, bool) {
    if (auto* attention = act::Attention::instance())
        return attention->sub_7100D75460();
    return true;
}

bool AttCheckNoCarry::check(act::Actor*, const act::ActorConstDataAccess&, const sead::Matrix34f*,
                            const sead::Vector3f&, const AttCheck_Unk1*, bool, bool) {
    if (auto* attention = act::Attention::instance())
        return !attention->sub_7100D75460();
    return true;
}

bool AttCheckGrab::check(act::Actor* actor, const act::ActorConstDataAccess&,
                         const sead::Matrix34f*, const sead::Vector3f&, const AttCheck_Unk1*, bool,
                         bool) {
    if (!actor)
        return false;
    if (actor->getActorFlags2().isOn(act::Actor::ActorFlag2::_40000000))
        return false;
    auto* info = actor->m100();
    if (!info)
        return true;
    return !info->_bc;
}

// NON_MATCHING: scheduling only (the original computes `activated != 0` before `ok ^ 1`)
bool AttCheckBootFirstTower::check(act::Actor*, const act::ActorConstDataAccess&,
                                   const sead::Matrix34f*, const sead::Vector3f&,
                                   const AttCheck_Unk1*, bool, bool) {
    auto* mgr = gdt::Manager::instance();
    if (!mgr)
        return true;
    bool activated = false;
    const bool ok = gdt::getBoolByName(mgr, &activated, "FindDungeon_Activated");
    return activated || !ok;
}

bool AttCheckFireContact::check(act::Actor*, const act::ActorConstDataAccess&,
                                const sead::Matrix34f*, const sead::Vector3f&,
                                const AttCheck_Unk1*, bool, bool) {
    if (auto* attention = act::Attention::instance())
        return !attention->sub_7100D75478();
    return false;
}

bool AttCheckCharacterOn::check(act::Actor* actor, const act::ActorConstDataAccess&,
                                const sead::Matrix34f*, const sead::Vector3f&,
                                const AttCheck_Unk1* arg, bool a6, bool) {
    if (arg)
        return true;
    return !act::sub_7100EE66C4(actor, a6);
}

bool AttCheckUnderWater::check(act::Actor* actor, const act::ActorConstDataAccess&,
                               const sead::Matrix34f*, const sead::Vector3f&,
                               const AttCheck_Unk1*, bool, bool) {
    return actor && actor->get6f4() <= 0.99f;
}

void AttCheckAngle::m4(act::Actor* actor, sead::Matrix34f* mtx) {
    mAttPos.x_2(mtx, actor);
}

// NON_MATCHING: register allocation / scheduling (the original keeps the direction in s8 / s9 the other way round, spills
// nothing and branches to a shared `return false` in the final comparisons instead of merging them into a `cset`)
bool AttCheckAngle::check(act::Actor* actor, const act::ActorConstDataAccess& accessor,
                          const sead::Matrix34f* mtx, const sead::Vector3f&, const AttCheck_Unk1*,
                          bool, bool) {
    const sead::Vector3f& actor_pos = actor->getPreviousPos();
    sead::Vector3f dir = accessor.getPreviousPos() - actor_pos;
    dir.y = 0.0f;
    if (dir.normalize() != 0.0f) {
        sead::Vector3f right(-mtx->m[2][0], 0.0f, mtx->m[0][0]);
        if (right.normalize() != 0.0f) {
            sead::Vector3f front;
            accessor.getActorMtx().getBase(front, 2);
            front.y = 0.0f;
            if (front.normalize() != 0.0f) {
                const f32 dot_dir_right = dir.dot(right);
                const f32 dot_right_front = right.dot(front);
                const f32 cos_angle = sead::Mathf::cos(mAngle.ref());
                if (dot_dir_right > 0.0f) {
                    if (!(dot_right_front <= -cos_angle))
                        return false;
                    return true;
                }
                if (!(cos_angle <= dot_right_front))
                    return false;
                return true;
            }
        }
    }
    return false;
}

bool AttCheckAngle::parse(const CreateArg& arg) {
    mAttPos.init(&mObj);
    mAngle.init(0.0, "Angle", "角度", "Min=0.f,Max=3.1415f", &mObj);
    return AttCheck::parse(arg);
}

bool AttCheck::parse(const CreateArg& arg) {
    return true;
}

namespace {
struct AttCheckFactory {
    const char* name;
    AttCheck* (*make)(AttCheckType type, sead::Heap* heap);
};

template <typename T>
constexpr AttCheckFactory makeFactory(const char* name) {
    AttCheckFactory factory{};
    factory.name = name;
    factory.make = [](AttCheckType type, sead::Heap* heap) -> AttCheck* {
        return new (heap) T(type);
    };
    return factory;
}

sead::SafeArray<AttCheckFactory, 19> sFactories{{
    makeFactory<AttCheckLine>("Line"),
    makeFactory<AttCheckScreen>("Screen"),
    makeFactory<AttCheckAreaSphere>("AreaSphere"),
    makeFactory<AttCheckAreaFan>("AreaFan"),
    makeFactory<AttCheckAreaCylinderFan>("AreaCylinderFan"),
    makeFactory<AttCheckAreaBox>("AreaBox"),
    makeFactory<AttCheckEachOtherArea>("EachOtherArea"),
    makeFactory<AttCheckAngle>("Angle"),
    makeFactory<AttCheckWeight>("Weight"),
    makeFactory<AttCheckRideHorse>("RideHorse"),
    makeFactory<AttCheckRideSpace>("RideSpace"),
    makeFactory<AttCheckSwim>("Swim"),
    makeFactory<AttCheckCarry>("Carry"),
    makeFactory<AttCheckNoCarry>("NoCarry"),
    makeFactory<AttCheckGrab>("Grab"),
    makeFactory<AttCheckBootFirstTower>("BootFirstTower"),
    makeFactory<AttCheckFireContact>("FireContact"),
    makeFactory<AttCheckCharacterOn>("CharacterOn"),
    makeFactory<AttCheckUnderWater>("UnderWater"),
}};
}  // namespace

AttCheck* AttCheck::make(const CreateArg& arg) {
    const auto Parameters = agl::utl::getResParameterObj(arg.res_list, "Parameters");
    if (!Parameters)
        return nullptr;

    int type = sFactories.size();
    const auto CheckType = agl::utl::getResParameter(Parameters, "CheckType");
    const sead::SafeString check_type_str = CheckType.getData<char>();
    for (int i = 0; i < sFactories.size(); ++i) {
        if (check_type_str == sFactories[i].name) {
            type = i;
            break;
        }
    }

    if (type == sFactories.size())
        return nullptr;

    auto* check = sFactories[type].make(AttCheckType(type), arg.heap);
    if (!check)
        return nullptr;

    if (!check->init(arg)) {
        delete check;
        return nullptr;
    }

    return check;
}

bool AttCheck::init(const AttCheck::CreateArg& arg) {
    mList.addObj(&mObj, "Parameters");
    mClient = arg.client;
    return parse(arg);
}

}  // namespace ksys::res
