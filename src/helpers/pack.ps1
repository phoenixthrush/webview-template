$exePath = "build/bin/*.exe"
$dllPath = "build/bin/libwebview.dll"

if (Test-Path $exePath) {
    Write-Host "$exePath found."

    if (Get-Command upx -ErrorAction SilentlyContinue) {
        $arch = [System.Environment]::GetEnvironmentVariable("PROCESSOR_ARCHITECTURE")
        $id = [System.Environment]::GetEnvironmentVariable("PROCESSOR_IDENTIFIER")

        if ($arch -match "ARM64" -or $id -match "ARM|AArch64") {
            Write-Host "ARM system detected. Skipping UPX compression."
        } else {
            Write-Host "Compressing with UPX..."
            upx --best $exePath
        }
    } else {
        Write-Host "UPX not found."
    }
} else {
    Write-Host "$exePath not found."
}

if (Test-Path $dllPath) {
    Remove-Item $dllPath -Force
}
