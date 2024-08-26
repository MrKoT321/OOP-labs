set PROGRAM="%~1"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% test-data\matrix3x3.txt > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\matrix3x3-expected.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\empty.txt > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err

%PROGRAM% test-data\zero_determinant.txt > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err

%PROGRAM% test-data\matrix2x2.txt > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1