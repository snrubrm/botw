#include "Game/gameStage.h"
#include "Game/gameScene.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldEnvMgr.h"

namespace uking {

// 0x71025cb0e9: set while the title stage exists (its init stores true, its destructor false). Next to the
// GameScene statics (0x71025cb0e0 / 0x71025cb0ea).
bool sIsTitleStageActive;

TitleStage::TitleStage() : mHeap(nullptr), _18(nullptr), _20(nullptr), _28(nullptr), _30(nullptr) {}

TitleStage::~TitleStage() {
    sIsTitleStageActive = false;
    mHeap->destroy();
}

StartupSaveCheckStage::StartupSaveCheckStage() : mHeap(nullptr), mState(nullptr) {}

StartupSaveCheckStage::~StartupSaveCheckStage() {
    mHeap->destroy();
}

void IndoorStage::initForStageGen() {
    ksys::world::sub_71010D6094(ksys::world::Manager::instance()->getEnvMgr());
}

IndoorStage::~IndoorStage() {
    mHeap->destroy();
}

bool IndoorStage::m2(sead::BufferedSafeString* out) {
    out->copy(mMapName);
    return true;
}

bool IndoorStage::getMapName(sead::BufferedSafeString* out, int x, int z) {
    if (x != 5 || z != 4)
        return false;
    out->copy(mMapName);
    return true;
}

void IndoorStage::m4(int* x, int* z, const sead::SafeString& name) {
    *x = 5;
    *z = 4;
}

void IndoorStage::getMapType(sead::BufferedSafeString* out) {
    out->copy(GameScene::getCurrentMapType());
}

int IndoorStage::m0() {
    return 1;
}

MainFieldDungeonStage::~MainFieldDungeonStage() {
    mHeap->destroy();
}

bool MainFieldDungeonStage::m2(sead::BufferedSafeString* out) {
    out->copy(mMapName);
    return true;
}

bool MainFieldDungeonStage::getMapName(sead::BufferedSafeString* out, int x, int z) {
    if (x != 5 || z != 4)
        return false;
    out->copy(mMapName);
    return true;
}

void MainFieldDungeonStage::m4(int* x, int* z, const sead::SafeString& name) {
    *x = 5;
    *z = 4;
}

void MainFieldDungeonStage::getMapType(sead::BufferedSafeString* out) {
    out->copy(GameScene::getCurrentMapType());
}

int MainFieldDungeonStage::m0() {
    return 2;
}

s32 ViewerStage::getType() {
    return 5;
}

void ViewerStage::initForStageGen() {
    ksys::world::sub_71010D6094(ksys::world::Manager::instance()->getEnvMgr());
}

}  // namespace uking
