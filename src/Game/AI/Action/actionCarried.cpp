#include "Game/AI/Action/actionCarried.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7100739498.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actUnk_7100e4e084.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectLiftable.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

Carried::Carried(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Carried::~Carried() = default;

bool Carried::init_(sead::Heap* heap) {
    if (*mIsUseConstraint_s) {
        if (!_110.init(heap))
            return false;
    }
    return true;
}

void Carried::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    auto* carrier = sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcParent());
    actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_4000);
    _68 = 0;
    if (*mIsOnBaseLink_s)
        actor->emitBasicSigOn();
    _110.x();
    _110.x_0();
    auto* bind = m34();
    bind->x(sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcParent()));
    m35();
    bind->_18 = true;
    if (auto* unit = actor->m100()) {
        unit->sub_7100E50450(carrier);
        unit->_124 = sub_710072DC58(actor);
        sead::Matrix34f mtx;
        if (m33(&mtx, &sub_71005DC5AC(actor))) {
            const sead::Matrix34f converted = _110.x_1(mtx);
            unit->sub_7100E4FCE8(60.0f * sead::Mathf::pi(), &converted);
            _110.x_2(mtx);
        } else {
            unit->sub_7100E4FCE8(60.0f * sead::Mathf::pi(), &actor->getMtx());
        }
        const f32 a = unit->sub_7100E4EDB8();
        if (getGParamList() && getGParamList()->getLiftable()) {
            _110.x_3(a, f32(getGParamList()->getLiftable()->mLiftRotFrame.ref()));
        }
        m36(&sub_71005DC57C(actor));
    }
    actor->sub_71011DA824(bind);
    if (auto* parent = sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcParent())) {
        sub_7100738C88(actor, parent);
        sub_7100738D28(actor, parent);
    }
    actor->x_22(sead::Vector3f::zero, sead::Vector3f::zero);
    if (*mIsCreateItem_s && actor->getMapObject()) {
        _110.updateIsDroppedFlag();
        actor->createDrops(0, 0);
    }
    _110.x_5();
    _110.x_6();
    if (!mHoldOnXLinkKey_s.isEmpty())
        xlinkSearchAndEmit(mActor, mHoldOnXLinkKey_s.cstr(), 1, nullptr);
    if (*mIsChangeable_s)
        mFlags.set(Flag::Changeable);
}

void Carried::loadParams_() {
    getStaticParam(&mBindType_s, "BindType");
    getStaticParam(&mFailDistance_s, "FailDistance");
    getStaticParam(&mIsCreateItem_s, "IsCreateItem");
    getStaticParam(&mIsRecoverCharCtrlAxis_s, "IsRecoverCharCtrlAxis");
    getStaticParam(&mIsUseConstraint_s, "IsUseConstraint");
    getStaticParam(&mIsOnBaseLink_s, "IsOnBaseLink");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mHoldOnXLinkKey_s, "HoldOnXLinkKey");
}

void Carried::calc_() {
    ksys::act::ai::Action::calc_();
}

void Carried::leave_() {
    auto* actor = mActor;
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_4000);
    if (*mIsUseConstraint_s) {
        _110.x_10();
        _110.x_11();
    }
    _110.x_12();
    const sead::Matrix34f mtx = actor->getMtx();
    sead::Vector3f pos;
    sub_7100739438(actor, &pos);
    actor->sub_71011DA834(m34());
    _110.x_13(mtx, *mIsRecoverCharCtrlAxis_s, pos);
    sub_7100738DC8(actor);
    sub_7100738DDC(actor);
    if (auto* unit = actor->m100()) {
        const f32 value = unit->_124;
        unit->_b0 = 0;
        unit->_b8 = 0;
        sub_710072DC9C(actor, value);
        unit->_124 = 1.0f;
    }
}

bool Carried::hasUpdateForPreDeleteCb() {
    return true;
}

bool Carried::updateForPreDelete() {
    return _110.sub_71006F8AB4();
}

bool Carried::m32() {
    if (*mFailDistance_s > 0.0f) {
        sead::Matrix34f mtx;
        sub_7100739498(mActor, &mtx);
        sead::Vector3f pos;
        mActor->getMtx().getTranslation(pos);
        sead::Vector3f target;
        mtx.getTranslation(target);
        const sead::Vector3f diff = pos - target;
        if (diff.squaredLength() > *mFailDistance_s * *mFailDistance_s)
            return true;
    }
    return false;
}

void Carried::m35() {
    _70._28 = sub_71005DC5AC(mActor).cstr();
    _70._30.getKey().reset();
    _70._68 = sub_71005DC57C(mActor);
    _70._98 = (*mBindType_s == 1) << 2;
}

bool Carried::m33(sead::Matrix34f* out, const sead::SafeString* bone) {
    auto* parent = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent());
    if (!out || !parent)
        return false;
    if (!sub_7100739178(mActor, bone, out))
        return false;
    if (*mBindType_s == 1) {
        const sead::Matrix34f& parent_mtx = parent->getMtx();
        const f32 x = out->m[0][3];
        const f32 y = out->m[1][3];
        const f32 z = out->m[2][3];
        *out = parent_mtx;
        out->m[0][3] = x;
        out->m[1][3] = y;
        out->m[2][3] = z;
    }
    return true;
}

}  // namespace uking::action
