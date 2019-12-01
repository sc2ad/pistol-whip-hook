// IMPORTANT!
// In order to properly build this library, you must provide an ndkpath.txt which points to your ndk-bundle directory
// This is used in the build and debug powershell scripts, which will build/debug for you.
// Author: Sc2ad

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "../../shared/utils/typedefs.h"
#include "../../shared/inline-hook/And64InlineHook.hpp"

#include "../../shared/utils/il2cpp-utils.hpp"
#include "../../shared/utils/utils.h"
#include "../../shared/utils/utils-functions.hpp"
#include "../../shared/utils/logging.h"

#define MAIN_ComputeStringHashOffset 0xE3BCEC
#define Sirenix_ComputeStringHashOffset 0xF26B98
#define Used_ComputeStringHashOffset 0x10CE8A4
#define Another_ComputeStringHashOffset 0xE07AA0
#define GetIDFromStringOffset 0xD5CBA8
#define KoreographyTrackBase_OnAfterDeserialize 0x1480590
#define KoreographyTrackBase_get_ID 0x147EEE4
#define AkBankManager_LoadBankOffset 0xE3C028
#define AkSoundEngine_LoadBank1Offset 0xD4C178
#define AkSoundEngine_LoadBank2Offset 0xD5FE20

MAKE_HOOK(MAIN_ComputeStringHash, MAIN_ComputeStringHashOffset, uint32_t, Il2CppString* s) {
    log(INFO, "Performing Main Namespace Hash on input string: %s", to_utf8(csstrtostr(s)).data());
    auto ret = MAIN_ComputeStringHash(s);
    log(INFO, "Result: %ui", ret);
    return ret;
}

MAKE_HOOK(Sirenix_ComputeStringHash, Sirenix_ComputeStringHashOffset, uint32_t, Il2CppString* s) {
    log(INFO, "Performing Sirenix Hash on input string: %s", to_utf8(csstrtostr(s)).data());
    auto ret = Sirenix_ComputeStringHash(s);
    log(INFO, "Result: %ui", ret);
    return ret;
}

MAKE_HOOK(Used_ComputeStringHash, Used_ComputeStringHashOffset, uint32_t, Il2CppString* s) {
    log(INFO, "Performing Used Hash on input string: %s", to_utf8(csstrtostr(s)).data());
    auto ret = Used_ComputeStringHash(s);
    log(INFO, "Result: %ui", ret);
    return ret;
}

MAKE_HOOK(Another_ComputeStringHash, Another_ComputeStringHashOffset, uint32_t, Il2CppString* s) {
    log(INFO, "Performing Another Hash on input string: %s", to_utf8(csstrtostr(s)).data());
    auto ret = Another_ComputeStringHash(s);
    log(INFO, "Result: %ui", ret);
    return ret;
}

MAKE_HOOK(GetIDFromString, GetIDFromStringOffset, uint32_t, Il2CppString* s) {
    log(INFO, "Performing GetIDFromString on input string: %s", to_utf8(csstrtostr(s)).data());
    auto ret = GetIDFromString(s);
    log(INFO, "Result: %ui", ret);
    return ret;
}

// MAKE_HOOK(OnTrackDeserialize, KoreographyTrackBase_OnAfterDeserialize, void, Il2CppObject* self) {
//     log(INFO, "Performing Koreography OnTrackDeserialize on: %p", self);
//     OnTrackDeserialize(self);
// }

MAKE_HOOK(get_ID, KoreographyTrackBase_get_ID, Il2CppString*, Il2CppObject* self) {
    log(INFO, "Performing Koreography get_ID on: %p", self);
    auto ret = get_ID(self);
    log(INFO, "Returned ID: %p", ret);
    if (ret) {
        log(INFO, "ID: %s", to_utf8(csstrtostr(ret)).data());
    }
    return ret;
}

MAKE_HOOK(LoadBank, AkBankManager_LoadBankOffset, void, Il2CppString* name, bool decodeBank, bool saveDecodedBank) {
    log(INFO, "Entering LoadBank Hook!");
    if (name) {
        log(INFO, "With name: %s", to_utf8(csstrtostr(name)).data());
    }
    LoadBank(name, decodeBank, saveDecodedBank);
    log(INFO, "Called LoadBank!");
}

MAKE_HOOK(SoundEngine_LoadBank1, AkSoundEngine_LoadBank1Offset, int, void* intPtr, uint32_t inMemorySize, uint32_t* outBankID) {
    log(INFO, "Entering SoundEngine.LoadBank1 Hook!");
    auto outp = SoundEngine_LoadBank1(intPtr, inMemorySize, outBankID);
    log(INFO, "Called LoadBank!");
    log(INFO, "Resulting ID: %u", *outBankID);
    log(INFO, "AKRESULT: %i", outp);
    return outp;
}

MAKE_HOOK(SoundEngine_LoadBank2, AkSoundEngine_LoadBank2Offset, int, Il2CppString* name, int inMemoryPoolID, uint32_t* outBankID) {
    log(INFO, "Entering SoundEngine.LoadBank2 Hook!");
    if (name) {
        log(INFO, "With name: %s", to_utf8(csstrtostr(name)).data());
    }
    auto outp = SoundEngine_LoadBank2(name, inMemoryPoolID, outBankID);
    log(INFO, "Called LoadBank!");
    log(INFO, "Resulting ID: %u", *outBankID);
    log(INFO, "AKRESULT: %i", outp);
    return outp;
}

static bool installed = false;
void InstallHooks() {
    if (installed) return;
    // log(INFO, "Installing HashMod!");
    // INSTALL_HOOK(MAIN_ComputeStringHash);
    // log(INFO, "Installed Main Hash hook!");
    // INSTALL_HOOK(Sirenix_ComputeStringHash);
    // log(INFO, "Installed Sirenix Hash hook!");
    // INSTALL_HOOK(Used_ComputeStringHash);
    // log(INFO, "Installed Used Hash hook!");
    // INSTALL_HOOK(Another_ComputeStringHash);
    // log(INFO, "Installed Another Hash hook!");
    // INSTALL_HOOK(GetIDFromString);
    // log(INFO, "Installed GetIDFromString hook!");
    // INSTALL_HOOK(OnTrackDeserialize);
    // log(INFO, "Installed OnTrackDeserialize hook!");
    // INSTALL_HOOK(get_ID);
    // log(INFO, "Installed get_ID hook!");
    INSTALL_HOOK(LoadBank);
    log(INFO, "Installed LoadBank hook!");
    INSTALL_HOOK(SoundEngine_LoadBank1);
    log(INFO, "Installed AkSoundEngine.LoadBank1 hook!");
    INSTALL_HOOK(SoundEngine_LoadBank2);
    log(INFO, "Installed AkSoundEngine.LoadBank2 hook!");
    log(INFO, "Installed HashMod!");
    installed = true;
}

__attribute__((constructor)) void lib_main() {
    InstallHooks();
}

extern "C" void load() {
    InstallHooks();
}