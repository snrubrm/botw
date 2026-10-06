#include "Game/AI/AI/aiBowShoot.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ui {
void sub_7100A94AA8(bool value);
}

namespace uking::ai {

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

}  // namespace uking::ai
