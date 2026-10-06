#include "Game/AI/AI/aiCommonPickedItem.h"
#include "Game/AI/aiUnk_71005E0420.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

// Declaration only; the original global source namespace is unknown.
bool sub_710072B8E8(ksys::act::Actor* actor);

namespace uking::ai {

CommonPickedItem::CommonPickedItem(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CommonPickedItem::~CommonPickedItem() {
    _d0.freeBuffer();
}

bool CommonPickedItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

bool CommonPickedItem::handleMessage_(const ksys::Message* message) {
    if (!isCurrentChild("通常"))
        return false;
    auto* actor = mActor;
    if (sub_710072B8E8(actor))
        return true;
    return handleItemPickedMessageMaybe(*message, &_88, actor, nullptr);
}

void CommonPickedItem::sub_7100355818() {
    auto* actor = mActor;
    _88.x();
    if (--_c8 <= 0)
        ksys::act::disableAttClient(actor, "NoticeDo");
    m35();
    actor->emitBasicSigOn();
    if (!_d0.getBufferPtr()) {
        changeChild("メインボタン");
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addString(_d0[_e0 - 1 - _c8], "GetActorName", -1);
        changeChild("メインボタン", &pack);
    }
}

void CommonPickedItem::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!_d0.getBufferPtr()) {
        _c8 = 1;
        _e0 = 1;
    }
    _88._34 = 0x1800029;
    _88.x();
    m34();
    m37();
    m38();
}

void CommonPickedItem::leave_() {
    ksys::act::disableAllAttClients(mActor);
}

void CommonPickedItem::calc_() {
    auto* actor = mActor;
    _88.sub_710070AE18(actor);
    if (!_88._30 && isCurrentChild("通常")) {
        auto* child = getCurrentChild();
        if (child) {
            if (child->isFinished()) {
                setFinished();
                return;
            }
            if (child->isFailed()) {
                setFailed();
                return;
            }
        }
    }
    if (sub_710072B8E8(actor))
        m35();
    if (_c8 > 0) {
        m37();
        if (ksys::act::attentionStuff_0(actor) || isCurrentChild("通常")) {
            if (_88._30 && !_88._39 && !_88._3a) {
                if (_88._38 == 1) {
                    auto* current_actor = mActor;
                    _88.x();
                    if (--_c8 <= 0)
                        ksys::act::disableAttClient(current_actor, "NoticeDo");
                    changeChild("サブボタン");
                } else {
                    sub_7100355818();
                }
            }
        } else {
            m38();
        }
    } else if (getCurrentChild()->isChangeable() || getCurrentChild()->isFinished()) {
        if (!isCurrentChild("消滅")) {
            _88.x();
            ksys::act::disableAllAttClients(mActor);
            changeChild("消滅");
        }
    }
}

void CommonPickedItem::loadParams_() {
    getStaticParam(&mCanGetOnBurning_s, "CanGetOnBurning");
    getStaticParam(&mIsControlNoticeDo_s, "IsControlNoticeDo");
    getStaticParam(&mGetAttKeyName_s, "GetAttKeyName");
    getMapUnitParam(&mIsPlayerPut_m, "IsPlayerPut");
    getMapUnitParam(&mDropTable_m, "DropTable");
    getMapUnitParam(&mDropActor_m, "DropActor");
    getAITreeVariable(&mGetNumLeft_a, "GetNumLeft");
}

void CommonPickedItem::sub_7100355A14() {
    _88.x();
}

void CommonPickedItem::m35() {
    ksys::act::disableAllAttClients(mActor);
}

void CommonPickedItem::m38() {
    _88.x();
    m34();
    changeChild("通常");
}

void CommonPickedItem::m34() {
    auto* actor = mActor;
    if (actor->getFadeOutDeleteType() != 0)
        return;
    ksys::act::enableAttClient(actor, "NameBalloon");
    ksys::act::enableAttClient(actor, "AutoAim");
    if (ksys::act::itemIsForSale(actor)) {
        ksys::act::enableAttClient(actor, "Buy");
        ksys::act::disableAttClient(actor, m36());
    } else {
        ksys::act::enableAttClient(actor, m36());
        ksys::act::disableAttClient(actor, "Buy");
    }
}

void CommonPickedItem::m37() {
    auto* actor = mActor;
    if (*mCanGetOnBurning_s) {
        ksys::act::enableAttClient(actor, "NoticeDo");
        return;
    }

    auto* chemical = actor->sub_71011D8A44(0);
    if (!chemical)
        return;

    if (chemical->_c0 == 2) {
        m35();
        ksys::act::disableAttClient(actor, "NoticeDo");
    } else {
        m34();
        if (*mIsControlNoticeDo_s)
            ksys::act::enableAttClient(actor, "NoticeDo");
    }
}

}  // namespace uking::ai
