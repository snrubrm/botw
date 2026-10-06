#include "Game/gameNFP.h"

NFP* NFP::sInstance;  // 0x710260c120

void NFP::insertFunctions(uking::Unk_710243b770* listener) {
    _30->sub_F48478(listener);
}

void NFP::eraseFunctions(uking::Unk_710243b770* listener) {
    _30->sub_F484CC(listener);
}

void NFP::sub_F45E1C(const s32* amiibo_id) {
    _30->sub_F4851C(amiibo_id);
}

void NFP::sub_F45E24(const s32* amiibo_id) {
    _30->sub_F48570(amiibo_id);
}

bool NFP::returnFalse() const {
    return false;
}

bool NFP::sub_F45DC8() const {
    return (_30->_195 & 2) != 0;
}

bool NFP::sub_F45DFC() const {
    return (_30->_195 & 8) != 0;
}
