#include "Game/Actor/AI/aiWizzrobeWeatherMagic.h"
#include "Game/Actor/Damage/dmgInfoManager.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWizzrobe.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

WizzrobeWeatherMagic::WizzrobeWeatherMagic(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WizzrobeWeatherMagic::~WizzrobeWeatherMagic() = default;

bool WizzrobeWeatherMagic::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WizzrobeWeatherMagic::enter_(ksys::act::ai::InlineParamPack* params) {
    _78 = sead::DynamicCast<Unk_7102431fa8>(
        *static_cast<Unk_71025afb58**>(mWizzrobeMagicWeatherUnit_a));
    _74 = -1.0f;
    _70 = mActor->getMtx().m[1][3] + *mRiseLength_s;
    sub_71005FF9BC();
}

// NON_MATCHING: AS query initialization and receiver load scheduling differ.
void WizzrobeWeatherMagic::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("準備"))
            sub_71005FFE8C();
        else if (isCurrentChild("発動"))
            setFinished();
        return;
    }

    if (isCurrentChild("準備")) {
        if (auto* as_list = mActor->getASList(); as_list && as_list->x_4(0, 0)) {
            sub_71005FFE8C();
            return;
        }
    } else if (isCurrentChild("詠唱")) {
        if (!(_58.mTimer.value <= sead::Mathf::epsilon()))
            _58.sub_7100D3BCE4();
        if (_58.mTimer.value <= sead::Mathf::epsilon() && mActor->getASList() &&
            mActor->getASList()->x(71, nullptr, 0, 0,
                                  &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
            ksys::act::ai::InlineParamPack params;
            params.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("発動", &params);
            return;
        }
    } else if (isCurrentChild("発動")) {
        child->setDynamicParam(*mTargetPos_d, "TargetPos");
        ksys::as::ASList::Unk4 query;
        if (mActor->getASList() &&
            mActor->getASList()->x(71, &query, 0, 0,
                                  &ksys::as::ASList::Unk2::sub_71011637EC, true) &&
            query.name == "ShootMagic" && _78) {
            if (const auto* params = getGParamList()->getWizzrobe())
                _78->sub_7100741E54(params->mMagicWeatherType.ref());
        }
        return;
    } else {
        return;
    }

    child->setDynamicParam(*mTargetPos_d, "AttPos");
    sead::Vector3f position;
    sub_71005FFF84(&position);
    child->setDynamicParam(position, "TargetPos");
}

// NON_MATCHING: shared position transforms merge the native left/right arithmetic branches.
void WizzrobeWeatherMagic::sub_71005FFF84(sead::Vector3f* out) {
    if (!out)
        return;
    *out = mActor->getMtx().getTranslation();
    auto* as_list = mActor->getASList();
    if (!as_list)
        return;

    ksys::as::ASList::Unk4 query;
    if (as_list->x(47, &query, 0, 0, &ksys::as::ASList::Unk2::sub_710116383C, true)) {
        _74 = -1.0f;
        if (query.name == sead::SafeString("Right") || query.name == sead::SafeString("Left"))
            _74 = sead::Mathf::max(query._10, 2.0f);
    }

    if (as_list->x(47, &query, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
        f32 scale = 1.0f;
        if (_74 > 0.0f) {
            scale = sead::Mathf::sin((query._10 / _74) * sead::Mathf::pi());
            if (scale < 0.05f)
                scale = 0.05f;
            else if (scale > 1.0f)
                scale = 1.0f;
        }
        if (query.name == "Right")
            out->set(-scale, scale, 0.0f);
        else if (query.name == "Left")
            out->set(scale, scale, 0.0f);
        else
            return;
        out->setMul(mActor->getMtx(), *out);
        return;
    }

    if (!as_list->x(47, &query, 0, 0, &ksys::as::ASList::Unk2::sub_710116388C, true))
        return;
    if (query.name == "Right")
        out->set(-0.05f, 0.05f, 0.0f);
    else if (query.name == "Left")
        out->set(0.05f, 0.05f, 0.0f);
    else
        return;
    out->setMul(mActor->getMtx(), *out);
}

void WizzrobeWeatherMagic::leave_() {
    if (!act::DamageInfoMgr::instance()->get790().sub_7100672B00(mActor) && _78)
        _78->_c = 2;
}

void WizzrobeWeatherMagic::loadParams_() {
    getStaticParam(&mRiseLength_s, "RiseLength");
    getStaticParam(&mTimer_s, "Timer");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getAITreeVariable(&mWizzrobeMagicWeatherUnit_a, "WizzrobeMagicWeatherUnit");
}

bool WizzrobeWeatherMagic::isFinished() const {
    return ksys::act::ai::Ai::isFinished() ||
           (isCurrentChild("発動") && getCurrentChild()->isFinished());
}

void WizzrobeWeatherMagic::sub_71005FF9BC() {
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f pos;
    params.addVec3(*mTargetPos_d, "AttPos", -1);
    sub_71005FFF84(&pos);
    params.addVec3(pos, "TargetPos", -1);
    _58.mTimer = ksys::Timer(*mTimer_s, *mTimer_s);
    if (_78)
        _78->_c = 1;
    changeChild("準備", &params);
}

// 0x71005ffe8c
void WizzrobeWeatherMagic::sub_71005FFE8C() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    pack.addVec3(*mTargetPos_d, "AttPos", -1);
    sub_71005FFF84(&pos);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("詠唱", &pack);
}

}  // namespace uking::ai
