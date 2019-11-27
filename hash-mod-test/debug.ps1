& adb shell am set-debug-app -w --persistent com.cloudheadgames.pistolwhip 

$NDKPath = Get-Content $PSScriptRoot/ndkpath.txt

$buildScript = "$NDKPath/ndk-gdb"
if (-not ($PSVersionTable.PSEdition -eq "Core")) {
    $buildScript += ".cmd"
}

& $buildScript --launch -x gdb_commands.txt