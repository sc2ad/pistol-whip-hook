#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

// Location of libil2cpp.so
#define IL2CPP_SO_PATH "/data/app/com.cloudheadgames.pistolwhip-1/lib/arm64/libil2cpp.so"

#include <stdio.h>
#include <stdlib.h>
#include "typedefs.h"
#include "utils-functions.hpp"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

long long getRealOffset(void* offset);
long long baseAddr(const char* soname);

#define MAKE_HOOK(name, addr, retval, ...) \
void* addr_ ## name = (void*) addr; \
retval (*name)(__VA_ARGS__) = NULL; \
retval hook_ ## name(__VA_ARGS__) 

#define MAKE_HOOK_OFFSETLESS(name, retval, ...) \
retval (*name)(__VA_ARGS__) = NULL; \
retval hook_ ## name(__VA_ARGS__)

#define MAKE_HOOK_NAT(name, addr, retval, ...) \
void* addr_ ## name = (void*) addr; \
retval (*name)(__VA_ARGS__) = NULL; \
retval hook_ ## name(__VA_ARGS__) 

#ifdef __aarch64__

// ARM64 HOOKS

#include "../inline-hook/And64InlineHook.hpp"

#define INSTALL_HOOK(name) \
log(INFO, "Installing 64 bit hook!"); \
A64HookFunction((void*)getRealOffset(addr_ ## name),(void*) hook_ ## name, (void**)&name); \

#define INSTALL_HOOK_OFFSETLESS(name, methodInfo) \
log(INFO, "Installing 64 bit offsetless hook!"); \
A64HookFunction((void*)methodInfo->methodPointer,(void*) hook_ ## name, (void**)&name); \

#define INSTALL_HOOK_NAT(name) \
log(INFO, "Installing 64 bit native hook!"); \
A64HookFunction((void*)(addr_ ## name),(void*) hook_ ## name, (void**)&name); \

#define INSTALL_HOOK_DIRECT(name, addr) \
log(INFO, "Installing 64 bit direct hook!"); \
A64HookFunction((void*)addr, (void*) hook_ ## name, (void**)&name); \

#else

#ifdef _WINDOWS_

// PC HOOKS

#include "../../PolyHook_2_0/headers/Detour/x64Detour.hpp"
#include "../../PolyHook_2_0/headers/CapstoneDisassembler.hpp"
#include "../../PolyHook_2_0/headers/IHook.hpp"
#include "../../PolyHook_2_0/headers/Detour/x64Detour.hpp"
#include "../../PolyHook_2_0/headers/Detour/x86Detour.hpp"
#include "../../PolyHook_2_0/headers/Instruction.hpp"
#include "../../PolyHook_2_0/headers/Detour/ADetour.hpp"
#include "../../PolyHook_2_0/headers/Enums.hpp"

// TODO: Check to see if INSTALL_HOOKs need reference to gameAssembly handle, or perhaps rewrite getRealOffset?
#define INSTALL_HOOK(name) \
uint64_t outp_ ## name; \
PLH::CapstoneDisassembler dis_ ## name(PLH::Mode::x64); \
auto detour_ ## name = PLH::x64Detour((uint64_t*)addr_ ## name, (uint64_t*)hook_ ## name, &outp_ ## name, dis_ ## name); \
name = PLH::FnCast(outp, &name); \
detour_ ## name.hook(); \
dis_ ## name.~CapstoneDisassembler();

#define INSTALL_HOOK_OFFSETLESS(name, methodInfo) \
log(INFO, "Installing x64 bit offsetless hook!"); \
A64HookFunction((void*)methodInfo->methodPointer,(void*) hook_ ## name, (void**)&name); \

#define INSTALL_HOOK_NAT(name) \
log(INFO, "Installing x64 bit native hook!"); \
A64HookFunction((void*)(addr_ ## name),(void*) hook_ ## name, (void**)&name); \

#define INSTALL_HOOK_DIRECT(name, addr) \
log(INFO, "Installing x64 bit direct hook!"); \
A64HookFunction((void*)addr, (void*) hook_ ## name, (void**)&name); \

#else

// ARM32 HOOKS

#define INSTALL_HOOK(name) \
log(INFO, "Installing 32 bit hook!"); \
registerInlineHook((uint32_t)getRealOffset(addr_ ## name), (uint32_t)hook_ ## name, (uint32_t **)&name); \
inlineHook((uint32_t)getRealOffset(addr_ ## name)); \

#define INSTALL_HOOK_OFFSETLESS(name, methodInfo) \
log(INFO, "Installing 32 bit offsetless hook!"); \
registerInlineHook((uint32_t)methodInfo->methodPointer, (uint32_t)hook_ ## name, (uint32_t **)&name); \
inlineHook((uint32_t)methodInfo->methodPointer); \

#define INSTALL_HOOK_NAT(name) \
log(INFO, "Installing 32 bit native hook!"); \
registerInlineHook((uint32_t)(addr_ ## name), (uint32_t)hook_ ## name, (uint32_t **)&name); \
inlineHook((uint32_t)(addr_ ## name)); \

#define INSTALL_HOOK_DIRECT(name, addr) \
log(INFO, "Installing 32 bit offsetless hook!"); \
registerInlineHook((uint32_t)addr, (uint32_t)hook_ ## name, (uint32_t **)&name); \
inlineHook((uint32_t)addr); \

#endif /* __x86_64__ or other */

#endif /* __aarch64__ or other */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* UTILS_H_INCLUDED */