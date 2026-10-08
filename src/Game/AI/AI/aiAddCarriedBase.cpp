#include "Game/AI/AI/aiAddCarriedBase.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7100739498.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actUnk_7100e4e084.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectLiftable.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

AddCarriedBase::AddCarriedBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AddCarriedBase::~AddCarriedBase() {
    _68.finalize();
}

bool AddCarriedBase::init_(sead::Heap* heap) {
    if (*mIsUseConstraint_s) {
        if (!_68.init(heap))
            return false;
    }
    return true;
}

void AddCarriedBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    auto* carrier = sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcParent());
    actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_4000);
    _60 = 0;
    _68.x_14();
    _68.x_0();
    auto* bind = m35();
    bind->x(sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcParent()));
    m36();
    bind->_18 = true;
    if (auto* unit = actor->m100()) {
        unit->sub_7100E50450(carrier);
        unit->_124 = sub_710072DC58(actor);
        sead::Matrix34f mtx;
        if (sub_7100739178(actor, &sub_71005DC5AC(actor), &mtx)) {
            _68.x_2(mtx);
            const sead::Matrix34f converted = _68.x_1(mtx);
            unit->sub_7100E4FCE8(60.0f * sead::Mathf::pi(), &converted);
        } else {
            unit->sub_7100E4FCE8(60.0f * sead::Mathf::pi(), &mActor->getMtx());
        }
        const f32 a = unit->sub_7100E4EDB8();
        if (getGParamList() && getGParamList()->getLiftable()) {
            _68.x_3(a, f32(getGParamList()->getLiftable()->mLiftRotFrame.ref()));
        }
        m37(sub_71005DC57C(actor));
    }
    mActor->sub_71011DA824(bind);
    if (auto* parent = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent())) {
        sub_7100738C88(actor, parent);
        sub_7100738D28(actor, parent);
    }
    mActor->x_22(sead::Vector3f::zero, sead::Vector3f::zero);
    _68.x_5();
    _68.x_6();
    if (!mHoldOnXLinkKey_s.isEmpty())
        xlinkSearchAndEmit(mActor, mHoldOnXLinkKey_s.cstr(), 1, nullptr);
    changeChild("持ち上げられ中", nullptr);
}

void AddCarriedBase::calc_() {
    auto* actor = mActor;
    _68.x_4();
    _68.x_7();
    _68.x_8();
    _68.x_9();
    if (_68._2c & 1) {
        ksys::act::sub_7100EE5980(actor, sead::Vector3f::zero);
        if (!isFinished() && !isFailed()) {
            ksys::act::sub_7100EE58C0(actor, actor->getMtx());
            mActor->sub_71011DA834(m35());
        }
        if (_68.x_15())
            _68.x_10();
        setFinished();
        return;
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (!child->isFinished())
            setFailed();
        else
            setFinished();
    }

    auto* unit = actor->m100();
    auto* parent = sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcParent());
    if (unit) {
        switch (_60) {
        case 0:
            _60 = 1;
            break;
        case 1:
            _68.x_16();
            m37(sub_71005DC57C(actor));
            if ((!m38() || (_68._2c & 0x10)) && sub_71005DC49C(actor)) {
                _60 = 2;
                if (*mIsUseConstraint_s) {
                    m35()->_18 = false;
                    if (parent) {
                        _68.x_17(parent->m38());
                        _68.x_18(parent);
                    }
                }
                _68.x_19();
                if (isCurrentChild("持ち上げられ中"))
                    changeChild("行動", nullptr);
            }
            break;
        case 2:
        case 3:
            if ((_68._2c & 0x18) != 0x10) {
                _68.x_16();
                m37(sub_71005DC57C(actor));
            }
            break;
        }
    }

    if (_60 == 2 && m34()) {
        actor->resetConnectedCalcParent(false);
        return;
    }

    if (_68.x_15()) {
        _68.x_20();
        ksys::phys::RigidBody* body = nullptr;
        if (parent) {
            _68.x_21();
            body = sub_71007394DC(parent);
        }
        if (body)
            _68.x_22(body);
        else
            _68.x_10();
        _68.x_23(parent);
    }

    if (_60 != 3 && sub_71005DC520(actor)) {
        _60 = 3;
        _68.x_10();
        _68.x_11();
        m35()->_18 = true;
        sub_710072DC9C(actor, 1.0f);
    }

    if ((_68._2c & 1) || sub_71005DC470(actor) || sub_71005DC4C8(actor) || sub_71005DC4F4(actor))
        setFinished();
}

bool AddCarriedBase::updateForPreDelete() {
    return _68.sub_71006F8AB4();
}

bool AddCarriedBase::hasUpdateForPreDeleteCb() {
    return true;
}

void AddCarriedBase::leave_() {
    auto* actor = mActor;
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_4000);
    if (*mIsUseConstraint_s) {
        _68.x_10();
        _68.x_11();
    }
    _68.x_12();
    const sead::Matrix34f mtx = actor->getMtx();
    sead::Vector3f pos;
    sub_7100739438(actor, &pos);
    actor->sub_71011DA834(m35());
    _68.x_13(mtx, *mIsRecoverCharCtrlAxis_s, pos);
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

bool AddCarriedBase::m34() {
    if (*mFailDistance_s > 0.0f) {
        sead::Matrix34f mtx;
        sub_7100739498(mActor, &mtx);
        const sead::Vector3f diff = mActor->getMtx().getTranslation() - mtx.getTranslation();
        if (diff.squaredLength() > *mFailDistance_s * *mFailDistance_s)
            return true;
    }
    return false;
}

bool AddCarriedBase::m38() {
    return true;
}

void AddCarriedBase::loadParams_() {
    getStaticParam(&mFailDistance_s, "FailDistance");
    getStaticParam(&mIsRecoverCharCtrlAxis_s, "IsRecoverCharCtrlAxis");
    getStaticParam(&mIsUseConstraint_s, "IsUseConstraint");
    getStaticParam(&mHoldOnXLinkKey_s, "HoldOnXLinkKey");
}

}  // namespace uking::ai
