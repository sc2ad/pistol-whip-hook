$NDKPath = Get-Content $PSScriptRoot/ndkpath.txt

$buildScript = "$NDKPath/build/ndk-build"
if (-not ($PSVersionTable.PSEdition -eq "Core")) {
    $buildScript += ".cmd"
}

& $buildScript NDK_PROJECT_PATH=$PSScriptRoot APP_BUILD_SCRIPT=$PSScriptRoot/Android.mk NDK_APPLICATION_MK=$PSScriptRoot/Application.mk
& adb push libs/arm64-v8a/libhashmod.so /sdcard/Android/data/com.cloudheadgames.pistolwhip/files/mods/libhashmod.so