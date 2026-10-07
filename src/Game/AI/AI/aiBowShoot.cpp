#include "Game/AI/AI/aiBowShoot.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectBow.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ui {
void sub_7100A94AA8(bool value);
}

namespace uking::ai {

void BowShoot::sub_710033BDB4(const sead::SafeString& name) {
    if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor)) {
        ksys::act::ai::InlineParamPack params;
        params.addString(weapon->m164(), "NodeName", -1);
        sead::Vector3f rotation;
        weapon->m165(&rotation);
        params.addVec3(rotation, "RotOffset", -1);
        sead::Vector3f translation;
        weapon->m166(&translation);
        params.addVec3(translation, "TransOffset", -1);
        changeChild(name.cstr(), &params);
    }
}

bool BowShoot::sub_710033C888() {
    for (s32 i = 0; i < 20; ++i) {
        if (!mHandles[i].hasProcCreationFailed())
            return false;
    }
    return true;
}

BowShoot::BowShoot(const InitArg& arg) : ksys::act::ai::Ai(arg), mHandles() {}

BowShoot::~BowShoot() {
    for (auto& handle : mHandles)
        handle.deleteProc();
}

void BowShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710033BDB4("リロード");
    _38 = false;
    _1b8 = 0;
    _1ba = 0xff;
    bool arrow_changed = false;
    if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor)) {
        sead::FixedSafeString<32> arrow_name;
        weapon->bowGetArrowName(&arrow_name);
        if (!mArrowName.isEmpty())
            arrow_changed = mArrowName != arrow_name;
    }
    sub_7100338F38(arrow_changed);
}

bool BowShoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() == ksys::MessageType(0x80000c4)) {
        if (_18c == 0) {
            s32 num_ready = 0;
            bool enough = false;
            for (s32 i = 0; i < 20; ++i) {
                if (mHandles[i].isProcReady() && ++num_ready >= _190) {
                    enough = true;
                    break;
                }
            }
            if (!enough && !sub_710033C888())
                return false;
        }
        ui::sub_7100A94AA8(false);
    }
    return false;
}

bool BowShoot::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void BowShoot::leave_() {
    sub_710033BB98();
}

void BowShoot::sub_710033BB98() {
    const s32* life = mActor->getLife();
    if (!life || *life > 0 || !isCurrentChild("発射") || _190 < 1)
        return;
    s32 shot = 0;
    do {
        if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
            weapon && weapon->sub_71002EA0D4()) {
            f32 time = _180.value;
            if (shot != 0)
                time += f32(*mActor->getParam()->getRes().mGParamList->getBow()->mLeadShotInterval * shot);
            sub_710033B16C(time);
        } else if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
                   weapon && weapon->sub_71002EA16C()) {
            f32 time = _180.value;
            if (shot != 0)
                time += f32(*mActor->getParam()->getRes().mGParamList->getBow()->mRapidFireInterval * shot);
            sub_710033AA88(time);
        }
    } while (_18c < _190 && ++shot < _190);
}

}  // namespace uking::ai
