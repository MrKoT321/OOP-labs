set PROGRAM="%~1"

%PROGRAM% < test-data\empty.txt > "%TEMP%\empty.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\empty.txt" test-data\output-error.txt >nul
if ERRORLEVEL 1 goto err

%PROGRAM% < test-data\no-number-text.txt > "%TEMP%\no-number-text.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\no-number-text.txt" test-data\output-error.txt >nul
if ERRORLEVEL 1 goto err

%PROGRAM% < test-data\non-magic.txt > "%TEMP%\non-magic.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\non-magic.txt" test-data\output-non-magic.txt >nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1