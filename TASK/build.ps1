# Write-Host "Installing Choco"
# Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))

# Write-Host "Installing CMake"
# choco install cmake --pre 


Write-Host "Installing 7-Zip"
choco install 7zip.commandline

Write-Host "Installing OpenCV"
./install-opencv-choco.ps1

$env:Path += ";C:\tools\opencv\build\x64\vc15\bin;C:\tools\opencv\build"

Write-Host "Building Target Cerium"
Remove-Item -Recurse -Force  build -ErrorAction Ignore
New-Item -Path . -Name "build" -ItemType "directory"
Set-Location -Path ./build
& "cmake" ..
& "cmake" --build . --config Release
