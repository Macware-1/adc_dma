# build.ps1 - PowerShell build script for adc_dma
param (
    [string]$BUILD = "debug"  # Accepts 'debug' or 'release'
)

$TARGET = "build/firmware"

# Tools
$CC  = "arm-none-eabi-gcc"
$CXX = "arm-none-eabi-g++"
$LD  = "arm-none-eabi-gcc"
$CP  = "arm-none-eabi-objcopy"
$SIZE = "arm-none-eabi-size"

# Flags
$CFLAGS_DEBUG   = @("-O0", "-g")
$CFLAGS_RELEASE = @("-O2", "-g0")
$APPLICATION_FLAG = "-DNLED_BLINK"

if ($BUILD -eq "debug") {
    $CFLAGS = $CFLAGS_DEBUG + $APPLICATION_FLAG
} elseif ($BUILD -eq "release") {
    $CFLAGS = $CFLAGS_RELEASE + $APPLICATION_FLAG
} else {
    Write-Error "Unknown BUILD type: $BUILD. Use 'debug' or 'release'."
    exit 1
}

$CFLAGS_C  = @("-c") + $CFLAGS + @("-mcpu=cortex-m4", "-mthumb", "-ffreestanding", "-fno-builtin")
$CXXFLAGS  = @("-c") + $CFLAGS + @("-mcpu=cortex-m4", "-mthumb", "-std=c++11", "-fno-exceptions", "-fno-rtti", "-ffreestanding", "-fno-builtin")
$HEADER    = @("-Iinclude")
$LDFLAGS   = @("-nostdlib", "-nostartfiles", "-T", "linker.ld")
$CPFLAGS   = @("-Obinary")

if (-not (Test-Path "build")) { New-Item -ItemType Directory -Name build }

$C_SOURCES = Get-ChildItem src -Filter *.c | ForEach-Object { $_.FullName }
foreach ($src in $C_SOURCES) {
    $obj = "build/" + [IO.Path]::GetFileNameWithoutExtension($src) + ".o"
    Write-Host "Compiling $src -> $obj"
    & $CC @($HEADER + $CFLAGS_C + @("-o", $obj, $src))
}

$CPP_SOURCES = Get-ChildItem src -Filter *.cpp | ForEach-Object { $_.FullName }
foreach ($src in $CPP_SOURCES) {
    $obj = "build/" + [IO.Path]::GetFileNameWithoutExtension($src) + ".o"
    Write-Host "Compiling $src -> $obj"
    & $CXX @($HEADER + $CXXFLAGS + @("-o", $obj, $src))
}

$STARTUP = "startup.c"
$STARTUP_OBJ = "build/startup.o"
Write-Host "Compiling $STARTUP -> $STARTUP_OBJ (O0)"
& $CC @($HEADER + @("-c", "-O0", "-g0", "-mcpu=cortex-m4", "-mthumb", "-ffreestanding", "-fno-builtin") + @("-o", $STARTUP_OBJ, $STARTUP))

$OBJECTS = Get-ChildItem build -Filter *.o | ForEach-Object { $_.FullName }
Write-Host "Linking to $TARGET.elf"
& $LD @($LDFLAGS + @("-o", "$TARGET.elf") + $OBJECTS)

Write-Host "Creating binary $TARGET.bin"
& $CP @($CPFLAGS + @("$TARGET.elf", "$TARGET.bin"))

Write-Host "==== Size info (text = flash, data + bss = RAM) ===="
& $SIZE "$TARGET.elf"

$binSize = (Get-Item "$TARGET.bin").Length
Write-Host "==== Firmware binary size (bytes) ===="
Write-Host $binSize
