#include "Game/AI/AI/aiGanonBeastRoot.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_710070284C.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Damage/dmgDamageManager.h"
#include "Game/gameLastBossMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include "KingSystem/System/CameraMgr.h"

namespace uking::ai {

GanonBeastRoot::GanonBeastRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBeastRoot::~GanonBeastRoot() = default;

bool GanonBeastRoot::init_(sead::Heap* heap) {
    if (!sead::IsDerivedFrom<act::Enemy>(mActor))
        return false;
    _128 = false;
    if (auto* mgr = Unk_710260af28::instance())
        mgr->sub_7100F1ECE8(mActor->getModel());
    _50.sub_71007107CC(heap, *mGrudeCreateNum_s);
    return true;
}

// NON_MATCHING: the original merges the stores of 0x84 / 0x88 into one pair and stores 0x80 separately
void GanonBeastRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (isRootAiParamINot5()) {
        if (auto* mgr = LastBossMgr::instance())
            mgr->sub_7100677FFC(mActor);
    }

    if (!_128) {
        auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
        if (!enemy)
            return;
        enemy->_e90 = 4;
        sub_71007A397C(mActor);
        {
            ksys::act::ActorConstDataAccess accessor;
            for (auto* part : enemy->_1128.mList) {
                ksys::act::acquireActor(&part->mLink, &accessor);
                enemy->sendMessage(*accessor.getMessageTransceiverId(),
                                   ksys::MessageType(0x800002d), nullptr, true);
            }
            *mParams.mIsGanonBeastAngry_a = false;
            _128 = true;
        }
    }

    _50.sub_7100710890(80, 180);
    _50._6c = false;
    _50._3c = *mGrudePlayerDist_s + 30.0f;
    _50._34 = 30.0f;
    _50._38 = 45.0f;
    _50._30 = 30.0f;
    _50._6d = true;
    _110 = ksys::act::PlayerInfo::getSomeProcLink();
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_110, &accessor);
    sub_71005D8DE8(mActor, _110, &accessor.getActorMtx(), &accessor.getPreviousPos());
    sub_71005DBC94(mActor, 0, false, false, true, false, true);
    sub_71003E6254();
}

void GanonBeastRoot::calc_() {
    sead::Vector3f camera_dir;
    ksys::sub_7100D8C7FC(&camera_dir);
    _50._34 = sead::Mathf::clampMin(camera_dir.y * 5.0f, 0.0f) + 25.0f;
    if (*mParams.mIsGanonBeastAngry_a)
        _50.sub_7100710938();

    auto* actor = mActor;
    getCurrentChild()->setDynamicParam(sub_71005D9330(actor), "TargetPos");
    bool damaged = false;
    if (auto* damage_mgr = sub_710072BA90(actor)) {
        const s32 damage = damage_mgr->getDamage();
        damaged = damage > 0;
    }

    if (!isCurrentChild("リアクション")) {
        if (sub_71007028CC(mActor)) {
            changeChild("リアクション");
            return;
        }
        if (damaged) {
            changeChild("リアクション");
            return;
        }
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        sub_71003E6254();
    } else if (child->isChangeable()) {
        if (sub_7100702894(mActor) && !isCurrentChild("瀕死"))
            sub_71003E6254();
    }
}

void GanonBeastRoot::leave_() {
    _50.sub_7100710DE4();
    if (isActorDeletedOrDeleting()) {
        if (auto* mgr = LastBossMgr::instance())
            mgr->sub_710067807C(mActor);
    }
}

// NON_MATCHING: the original keeps `this + 0x38` in an extra callee-saved register (known loadParams_ frame
// difference)
void GanonBeastRoot::loadParams_() {
    getStaticParam(&mGrudeInterval3_s, "GrudeInterval3");
    getStaticParam(&mGrudeInterval4_s, "GrudeInterval4");
    getStaticParam(&mGrudeInterval5_s, "GrudeInterval5");
    getStaticParam(&mGrudeCreateNum_s, "GrudeCreateNum");
    getStaticParam(&mWeakPointASSlot_s, "WeakPointASSlot");
    getStaticParam(&mGrudePlayerDist_s, "GrudePlayerDist");
    getStaticParam(&mGrudeRandRange_s, "GrudeRandRange");
    getStaticParam(&mGrudeCenterOffset_s, "GrudeCenterOffset");
    getStaticParam(&mInitWeakPointASName_s, "InitWeakPointASName");
    getStaticParam(&_50.mGrudeRainObject_s, "GrudeRainObject");
    getStaticParam(&_50.mGrudeRainObject2_s, "GrudeRainObject2");
    getAITreeVariable(&mParams.mWeakPointAliveFlag_a, "WeakPointAliveFlag");
    getAITreeVariable(&mParams.mWeakPointActiveFlag_a, "WeakPointActiveFlag");
    getAITreeVariable(&mParams.mIsGanonBeastAngry_a, "IsGanonBeastAngry");
}

void GanonBeastRoot::sub_71003E6254() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    if (sub_7100702894(mActor))
        changeChild("瀕死", &pack);
    else
        changeChild("待機", &pack);
}

}  // namespace uking::ai
