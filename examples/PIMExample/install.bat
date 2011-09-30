SET TOOLS_PATH="c:\Work\Android\android-sdk\platform-tools"
SET ADB="adb.exe"
SET ARGS=install -r
SET APP_PATH="Output\Debug\android_7\1"
SET APP_NAME="PIMExample.apk"
SET APP_NAME1="PIMExample.apk"

%TOOLS_PATH%\%ADB% %ARGS% %APP_PATH%\\%APP_NAME%