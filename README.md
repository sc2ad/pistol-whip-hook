# pistol-whip-hook

This is Sc2ad's fork of jakibaki's modloader, which contains many new functions that the original library does not yet have. However, the code style/true validity (as in, "can it run?") of this repo are significantly more in question than the main library.

## Acknowledgements

This wouldn't have been possible without a few people who have helped immensely.

- [emulamer](https://github.com/emulamer/): Provided support, tested, and in general just a great person to talk to. This wouldn't exist at all if not for him motivating me to keep working.
- [jakibaki](https://github.com/jakibaki/): Created the library that actually supports all of the mod loading, as well as a lot of support when developing (and bearing with my annoying questions).

Right now this loads mods (`.so` files) from `/sdcard/Android/data/com.cloudheadgames.pistolwhip/files/mods/`

Uses [Android Inline Hook](https://github.com/ele7enxxh/Android-Inline-Hook) + some macros for magic

Copy-paste `libmain.so` and `libmodloader.so` built from `QuestLoader` to the same directory as `libil2cpp.so`, which should be: `/data/app/com.cloudheadgames.pistolwhip/lib/arm64-v8a/`

Follow [Frida Without Root](https://koz.io/using-frida-on-android-without-root/) to learn how to inject the modloader-library into the apk (with the so built from this instead of frida)

The function offsets (as well as infos about the structs) can be obtained with [Il2CppDumper](https://github.com/sc2ad/Il2CppDumper)

```ndk
ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk NDK_APPLICATION_MK=./Application.mk
```
