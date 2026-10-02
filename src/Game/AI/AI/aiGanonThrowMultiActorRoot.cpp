#include "Game/AI/AI/aiGanonThrowMultiActorRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

GanonThrowMultiActorRoot::GanonThrowMultiActorRoot(const InitArg& arg) : GanonThrowActorRoot(arg) {}

GanonThrowMultiActorRoot::~GanonThrowMultiActorRoot() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);

    if (!mPartsName1_s.isEmpty()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&enemy->getActorPartsActor(mPartsName1_s), &accessor);
        if (accessor.hasProc())
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        enemy->sub_7100D3CFEC(mPartsName1_s);
    }

    if (!mPartsName2_s.isEmpty()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&enemy->getActorPartsActor(mPartsName2_s), &accessor);
        if (accessor.hasProc())
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        enemy->sub_7100D3CFEC(mPartsName2_s);
    }

    if (!mPartsName3_s.isEmpty()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&enemy->getActorPartsActor(mPartsName3_s), &accessor);
        if (accessor.hasProc())
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        enemy->sub_7100D3CFEC(mPartsName3_s);
    }

    if (!mPartsName4_s.isEmpty()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&enemy->getActorPartsActor(mPartsName4_s), &accessor);
        if (accessor.hasProc())
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        enemy->sub_7100D3CFEC(mPartsName4_s);
    }

    if (!mPartsName5_s.isEmpty()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&enemy->getActorPartsActor(mPartsName5_s), &accessor);
        if (accessor.hasProc())
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        enemy->sub_7100D3CFEC(mPartsName5_s);
    }

    if (!mPartsName6_s.isEmpty()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&enemy->getActorPartsActor(mPartsName6_s), &accessor);
        if (accessor.hasProc())
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        enemy->sub_7100D3CFEC(mPartsName6_s);
    }

    if (!mPartsName7_s.isEmpty()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&enemy->getActorPartsActor(mPartsName7_s), &accessor);
        if (accessor.hasProc())
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        enemy->sub_7100D3CFEC(mPartsName7_s);
    }

    if (!mPartsName8_s.isEmpty()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&enemy->getActorPartsActor(mPartsName8_s), &accessor);
        if (accessor.hasProc())
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        enemy->sub_7100D3CFEC(mPartsName8_s);
    }
}

bool GanonThrowMultiActorRoot::init_(sead::Heap* heap) {
    if (!GanonThrowActorRoot::init_(heap))
        return false;

    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;

    if (sub_71005D6D10())
        return true;

    if (!mPartsName1_s.isEmpty()) {
        enemy->sub_7100D3CED8(mPartsName1_s, heap);
        auto* actor = sub_71003EF66C(1);
        if (!actor)
            return false;
        enemy->sub_7100D3D108(mPartsName1_s, actor);
    }

    if (!mPartsName2_s.isEmpty()) {
        enemy->sub_7100D3CED8(mPartsName2_s, heap);
        auto* actor = sub_71003EF66C(2);
        if (!actor)
            return false;
        enemy->sub_7100D3D108(mPartsName2_s, actor);
    }

    if (!mPartsName3_s.isEmpty()) {
        enemy->sub_7100D3CED8(mPartsName3_s, heap);
        auto* actor = sub_71003EF66C(3);
        if (!actor)
            return false;
        enemy->sub_7100D3D108(mPartsName3_s, actor);
    }

    if (!mPartsName4_s.isEmpty()) {
        enemy->sub_7100D3CED8(mPartsName4_s, heap);
        auto* actor = sub_71003EF66C(4);
        if (!actor)
            return false;
        enemy->sub_7100D3D108(mPartsName4_s, actor);
    }

    if (!mPartsName5_s.isEmpty()) {
        enemy->sub_7100D3CED8(mPartsName5_s, heap);
        auto* actor = sub_71003EF66C(5);
        if (!actor)
            return false;
        enemy->sub_7100D3D108(mPartsName5_s, actor);
    }

    if (!mPartsName6_s.isEmpty()) {
        enemy->sub_7100D3CED8(mPartsName6_s, heap);
        auto* actor = sub_71003EF66C(6);
        if (!actor)
            return false;
        enemy->sub_7100D3D108(mPartsName6_s, actor);
    }

    if (!mPartsName7_s.isEmpty()) {
        enemy->sub_7100D3CED8(mPartsName7_s, heap);
        auto* actor = sub_71003EF66C(7);
        if (!actor)
            return false;
        enemy->sub_7100D3D108(mPartsName7_s, actor);
    }

    if (!mPartsName8_s.isEmpty()) {
        enemy->sub_7100D3CED8(mPartsName8_s, heap);
        auto* actor = sub_71003EF66C(8);
        if (!actor)
            return false;
        enemy->sub_7100D3D108(mPartsName8_s, actor);
    }

    return true;
}

void GanonThrowMultiActorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    GanonThrowActorRoot::enter_(params);
}

void GanonThrowMultiActorRoot::calc_() {
    GanonThrowActorRoot::calc_();
}

void GanonThrowMultiActorRoot::leave_() {
    GanonThrowActorRoot::leave_();
}

void GanonThrowMultiActorRoot::loadParams_() {
    GanonThrowActorRoot::loadParams_();
    getStaticParam(&mPartsName1_s, "PartsName1");
    getStaticParam(&mPartsName2_s, "PartsName2");
    getStaticParam(&mPartsName3_s, "PartsName3");
    getStaticParam(&mPartsName4_s, "PartsName4");
    getStaticParam(&mPartsName5_s, "PartsName5");
    getStaticParam(&mPartsName6_s, "PartsName6");
    getStaticParam(&mPartsName7_s, "PartsName7");
    getStaticParam(&mPartsName8_s, "PartsName8");
}

// NON_MATCHING: scheduling of the first accessor's zero stores around `mov x0, parts`
bool GanonThrowMultiActorRoot::m34() const {
    if (!GanonThrowActorRoot::m34())
        return false;

    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;

    auto& parts = enemy->_1128;
    {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&parts.getActorPartsActor(mPartsName1_s), &accessor);
        if (accessor.hasProc() && accessor.isStateCalc())
            return false;
    }

    {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&parts.getActorPartsActor(mPartsName2_s), &accessor);
        if (accessor.hasProc() && accessor.isStateCalc())
            return false;
    }

    {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&parts.getActorPartsActor(mPartsName3_s), &accessor);
        if (accessor.hasProc() && accessor.isStateCalc())
            return false;
    }

    {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&parts.getActorPartsActor(mPartsName4_s), &accessor);
        if (accessor.hasProc() && accessor.isStateCalc())
            return false;
    }

    {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&parts.getActorPartsActor(mPartsName5_s), &accessor);
        if (accessor.hasProc() && accessor.isStateCalc())
            return false;
    }

    {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&parts.getActorPartsActor(mPartsName6_s), &accessor);
        if (accessor.hasProc() && accessor.isStateCalc())
            return false;
    }

    {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&parts.getActorPartsActor(mPartsName7_s), &accessor);
        if (accessor.hasProc() && accessor.isStateCalc())
            return false;
    }

    {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&parts.getActorPartsActor(mPartsName8_s), &accessor);
        if (accessor.hasProc() && accessor.isStateCalc())
            return false;
    }

    return true;
}

bool GanonThrowMultiActorRoot::m35() {
    if (!GanonThrowActorRoot::m35())
        return false;

    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;

    if (sub_71003F18A4(enemy, mPartsName1_s, false))
        return false;
    if (sub_71003F18A4(enemy, mPartsName2_s, false))
        return false;
    if (sub_71003F18A4(enemy, mPartsName3_s, false))
        return false;
    if (sub_71003F18A4(enemy, mPartsName4_s, false))
        return false;
    if (sub_71003F18A4(enemy, mPartsName5_s, false))
        return false;
    if (sub_71003F18A4(enemy, mPartsName6_s, false))
        return false;
    if (sub_71003F18A4(enemy, mPartsName7_s, false))
        return false;
    if (sub_71003F18A4(enemy, mPartsName8_s, false))
        return false;
    return true;
}

void GanonThrowMultiActorRoot::m36() {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(*mTargetPos_d, "TargetPos", -1);
    auto* target = sub_71005D9050(mActor);
    if (!target) {
        setFailed();
        return;
    }
    params.addActor(*target, "TargetActor", -1);
    params.addString(mRegisterPartsName_s, "ThrowPartsName", -1);
    params.addString(mPartsName1_s, "ThrowPartsName1", -1);
    params.addString(mPartsName2_s, "ThrowPartsName2", -1);
    params.addString(mPartsName3_s, "ThrowPartsName3", -1);
    params.addString(mPartsName4_s, "ThrowPartsName4", -1);
    params.addString(mPartsName5_s, "ThrowPartsName5", -1);
    params.addString(mPartsName6_s, "ThrowPartsName6", -1);
    params.addString(mPartsName7_s, "ThrowPartsName7", -1);
    params.addString(mPartsName8_s, "ThrowPartsName8", -1);
    changeChild("投げる", &params);
}

void GanonThrowMultiActorRoot::m38() {
    GanonThrowActorRoot::m38();
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;

    sub_71003F18A4(enemy, mPartsName1_s, true);
    sub_71003F18A4(enemy, mPartsName2_s, true);
    sub_71003F18A4(enemy, mPartsName3_s, true);
    sub_71003F18A4(enemy, mPartsName4_s, true);
    sub_71003F18A4(enemy, mPartsName5_s, true);
    sub_71003F18A4(enemy, mPartsName6_s, true);
    sub_71003F18A4(enemy, mPartsName7_s, true);
    sub_71003F18A4(enemy, mPartsName8_s, true);
}

bool GanonThrowMultiActorRoot::sub_71003F18A4(act::Enemy* enemy, const sead::SafeString& name,
                                              bool stop) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
    if (accessor.hasProc() && accessor.isStateCalc()) {
        if (stop) {
            if (*mIsSendDeleteMessageAtLeave_s)
                sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x800005c),
                            nullptr);
            else
                accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        }
        return true;
    }
    return false;
}

}  // namespace uking::ai
