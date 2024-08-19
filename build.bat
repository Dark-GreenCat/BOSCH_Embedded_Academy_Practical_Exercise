@ECHO OFF
@REM By check the headless-build.bat which come along with STM32CubeIDE.
@REM we can invoke the build process without invoking the GUI.

@REM Set PATH for STM32CubeIDE.
SET "CUBEIDE_PATH=C:\ST\STM32CubeIDE_1.13.1\STM32CubeIDE"
SET OLD_PATH=%PATH%
SET PATH=%CUBEIDE_PATH%;%PATH%

@REM Use stm32cubeidec.exe to build the project in specified workspace.
SET "WORKSPACE=D:\OneDrive - Hanoi University of Science and Technology\Documents\HUST\Learning Materials\BOSCH Embedded Automotive 2024\Assignment"
SET "PROJECT=BEA_CAN2CAN_DEMO_TEN1HC_HUST"
SET HEADLESS=--launcher.suppressErrors -nosplash -application org.eclipse.cdt.managedbuilder.core.headlessbuild
stm32cubeidec.exe %HEADLESS% -build %PROJECT% -data "%WORKSPACE%"

SET PATH=%OLD_PATH%
ECHO ON