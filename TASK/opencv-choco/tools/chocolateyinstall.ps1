$ErrorActionPreference = 'Stop';
# url for opencv-4.2.0
$url = 'https://github.com/opencv/opencv/releases/download/4.2.0/opencv-4.2.0-vc14_vc15.exe'
# for testing
# $url = 'C:\Users\shadowleaf\Downloads\Programs\opencv-4.2.0-vc14_vc15.exe'

$toolsDir = Get-ToolsLocation

# install in C:\tools\opencv\
$installationPath = Join-Path $toolsDir 'opencv'

Write-Host "Installing OpenCV to " $installationPath

# create the environment variable
Write-Host "Creating OPENCV_DIR environment variable."
$newpath = [environment]::GetEnvironmentVariable("Path", "User") + ";%OPENCV_DIR%\build\bin" + ";%OPENCV_DIR%\build\x64\vc15\bin"
[environment]::SetEnvironmentVariable("OPENCV_DIR", $installationPath, "User")
[environment]::SetEnvironmentVariable("Path", $newpath, "User")

$packageArgs = @{
    packageName    = $env:ChocolateyPackageName
    unzipLocation  = $toolsDir
    fileType       = 'EXE'
    url            = $url
    softwareName   = 'OpenCV-4.2.0'
    validExitCodes = @(0, 3010, 1641)
}

# install opencv
Install-ChocolateyZipPackage @packageArgs










    








