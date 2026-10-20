#pragma once

#include <container/seadObjArray.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include <utility/aglParameter.h>
#include "KingSystem/Quest/qstQuest.h"
#include "KingSystem/Resource/resHandle.h"

namespace uking::action {
class SetChallengeIcon;
}

namespace ksys::qst {

struct Quest;

class Manager {
    friend class uking::action::SetChallengeIcon;
    SEAD_SINGLETON_DISPOSER(Manager)
public:
    Manager();
    virtual ~Manager();

    void init(sead::Heap* heap);
    void cleanUp();
    // 0x7100fd76d4: frees the quest data and requests the quest pack again unless it loaded.
    void resetAndLoadQuestInfo();
    // 0x7100fd7820: polls the quest resource; parses it when needed. True once it is ready.
    bool sub_7100FD7820();
    // 0x7100fd7898: resets the stage-generation state and quest flags.
    void prepareFirstTimeGenStage();

    void auto0(act::Actor* actor);
    bool auto4(act::Actor* actor) const;

    // 0x7100fd78b0 (declared only)
    void sub_7100FD78B0(const sead::SafeString& quest_name);
    bool sub_7100FD78F8();

    bool sub_7100FD7B30(const sead::SafeString& quest_name, const sead::SafeString& step_name,
                        bool setAocVersionFlag1);
    bool setQuestStepFromEvent(const sead::SafeString& quest_name,
                               const sead::SafeString& step_name, bool force_run_telop,
                               bool setAocVersionFlag1);
    bool setQuestStep(const sead::SafeString& quest_name, const sead::SafeString& step_name,
                      bool copy_name, bool force_run_telop, bool setAocVersionFlag1);

    // Native FD7610 hashes this name and searches the existing quest array.
    Quest* sub_7100FD7610(const sead::SafeString& name) const;
    bool isQuestActor(act::Actor* actor) const;
    // 0x7100fd7460: whether an enabled quest camera target has this name.
    bool sub_7100FD7460(const sead::SafeString& name) const;
    static act::BaseProc* sub_7100FD5848(const sead::SafeString& s1, const sead::SafeString& s2);
    // 0x71007b15a8 / GameScene::unloadStage store the byte at +0x5d.
    void setUnk5D(bool value) { mUnk5D = value; }

private:
    u32 _28;
    u32 _2c;
    u32 _30;
    void* temp;
    u32 temp2;
    u32 _44;
    sead::PtrArray<const CameraTarget> _48;  // camera targets of all quest steps (sub_7100FD78F8)
    u32 _58;
    u8 _5c;
    // Set by GameScene::initBeforeStageGen and GameScene::unloadStage.
    bool mUnk5D;
    u8 _5e[2];
    u32 temp4;
    res::Handle mHandle;
    sead::ObjArray<Quest> mQuests;
    sead::Heap* mHeap = nullptr;
    u16 mFlags;
    u32 _e4;
    s32 _e8 = -1;
    u32 _d0 = 0;

    static bool sDisable;
};

}  // namespace ksys::qst
