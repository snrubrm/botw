#include "Game/AI/AI/aiGolemPartRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71006F5B14.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectChemicalType.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

GolemPartRoot::GolemPartRoot(const InitArg& arg) : ReuseBulletPartsRoot(arg) {}

GolemPartRoot::~GolemPartRoot() {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_c8, &accessor);
    if (accessor.hasProc() && accessor.isStateSleep())
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
}

// 0x71003fd684
// NON_MATCHING: the sub_71005D6D10 result tail keeps explicit if/else bool stores in the original;
// ours folds them into one move (3 instructions). Everything else matches, including the IsDerivedFrom
// shape, the pack setup, the DynamicCast blocks and both acquires.
bool GolemPartRoot::init_(sead::Heap* heap) {
    bool result = true;
    if (!ReuseBulletPartsRoot::init_(heap)) {
        result = false;
    } else {
        const auto* chem = mActor->getParam()->getRes().mGParamList->getChemicalType();
        const sead::SafeString* name = &sead::SafeString::cEmptyString;
        if (chem)
            name = &chem->mEmitChemicalActor.ref();
        if (name->getStringTop()[0] == sead::SafeString::cNullChar)
            return result;

        ksys::act::InstParamPack pack;
        pack->addMatrix(mActor->getMtx());
        pack->add(10.0f, "ScaleTime");
        pack->add(true, "IsReuseActor");
        ksys::act::ActorCreator::addScale(pack, *mChemFieldScale_s);
        pack->add(false, "IsUseAtCollision");

        auto* actor = ksys::act::ActorCreator::instance()->createActor(
            name->cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &pack, true,
            false);
        if (!actor) {
            if (sub_71005D6D10())
                result = true;
            else
                result = false;
        } else {
            if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(actor)) {
                auto* owner = mActor;
                if (sead::IsDerivedFrom<ksys::act::Bullet>(owner)) {
                    auto& link = owner->getCreateArgBaseProcLink();
                    if (link.hasProc()) {
                        bullet->sub_7100004988(link);
                        bullet->sub_71000048C8(link);
                    }
                }
                bullet->_bd0._0.acquire(mActor, false);
            }
            _c8.acquire(actor, false);
        }
    }
    return result;
}

// NON_MATCHING: register allocation of the loop count / the two flags (the logic is complete)
void GolemPartRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ReuseBulletPartsRoot::enter_(params);
    bool has_ice = false;
    bool has_burn = false;
    if (auto* chemicals = mActor->getChemicalContainer()) {
        const s32 count = chemicals->_58.size() + chemicals->_80;
        for (s32 i = 0; i < count; ++i) {
            auto* chemical = chemicals->sub_7100E37788(i);
            if (!chemical)
                continue;
            if (*mGolemPartInitialBurn_a) {
                if (chemical->_c0 == 2) {
                    has_burn = true;
                } else {
                    chemical->sub_7100D90858(false, 2, false, true, false);
                    has_burn = true;
                }
            } else if (chemical->_c0 == 2) {
                chemical->sub_7100D90B78();
            }
            if (chemical->mMaterial->attribute.ref() & 0x8000) {
                if (*mGolemPartInitialIceMagic_a) {
                    chemical->_bf &= ~2;
                    has_ice = true;
                } else {
                    chemical->_bf |= 2;
                }
            }
        }
    }

    if (!has_ice && !has_burn) {
        if (!mNormalAS_s.isEmpty())
            changeAS(mNormalAS_s.cstr(), false, 0, 0);
        xlinkEventOn(mActor, 26, 0, false);
    } else {
        if (!mActiveAS_s.isEmpty())
            changeAS(mActiveAS_s.cstr(), false, 0, 0);
        xlinkEventOn(mActor, 26, 1, false);
    }
}

bool GolemPartRoot::m34() {
    auto* actor = mActor;
    if (!isLandedMaybe(actor, false) && !isBgGroundHit(actor, false))
        return false;
    for (s32 i = 0, n = sub_71007A49F0(actor); i < n; ++i) {
        if (auto* entry = sub_71007A4948(actor, i)) {
            if (sub_71006F59C4(mActor, -1))
                sub_71003FDCF8(&entry->_0);
            return true;
        }
    }
    for (s32 i = 0, n = sub_71007A47C4(actor); i < n; ++i) {
        if (auto* entry = sub_71007A471C(actor, i)) {
            if (sub_71006F59C4(mActor, -1))
                sub_71003FDCF8(&entry->_0);
            return true;
        }
    }
    return true;
}

void GolemPartRoot::sub_71003FDCF8(const sead::Vector3f* pos) {
    if (_c8.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_c8, &accessor);
        if (accessor.hasProc() && accessor.isStateSleep()) {
            sead::Matrix34f mtx = sead::Matrix34f::ident;
            mtx.setTranslation(*pos);
            accessor.setProperties(mtx, nullptr, nullptr, nullptr, false, 0, -1);
        }
    }
}

void GolemPartRoot::calc_() {
    ReuseBulletPartsRoot::calc_();
}

void GolemPartRoot::leave_() {
    ReuseBulletPartsRoot::leave_();
}

void GolemPartRoot::loadParams_() {
    ReuseBulletPartsRoot::loadParams_();
    getStaticParam(&mChemFieldScale_s, "ChemFieldScale");
    getStaticParam(&mNormalAS_s, "NormalAS");
    getStaticParam(&mActiveAS_s, "ActiveAS");
    getAITreeVariable(&mGolemPartInitialIceMagic_a, "GolemPartInitialIceMagic");
    getAITreeVariable(&mGolemPartInitialBurn_a, "GolemPartInitialBurn");
}

}  // namespace uking::ai
