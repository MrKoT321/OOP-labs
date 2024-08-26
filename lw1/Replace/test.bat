set PROGRAM="%~1"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% test-data\empty.txt "%TEMP%\empty.txt" in out
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\empty.txt" test-data\empty-expected.txt >nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\replace-numbers.txt "%TEMP%\replace-numbers.txt" 123412345 cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\replace-numbers.txt" test-data\replace-numbers-expected.txt >nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\replace-numbers.txt "%TEMP%\no-replace-numbers.txt" cat 123412345
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\no-replace-numbers.txt" test-data\replace-numbers.txt >nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\replace-numbers.txt "%TEMP%\empty-replace-numbers.txt" "" cats
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\empty-replace-numbers.txt" test-data\replace-numbers.txt >nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\replace-numbers.txt "%TEMP%\replace-on-empty.txt" 123412345 ""
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\replace-on-empty.txt" test-data\replace-on-empty-output.txt >nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1