@echo off
setlocal EnableExtensions
pushd "%~dp0"

set "FILENAME=notebook"
set "BUILD_DIR=build"
set "LATEX_OPTION=-output-directory=%BUILD_DIR%"
set "LATEX_OPTION_QUIET=-interaction=batchmode -halt-on-error"
set "PYTHONUTF8=1"
set "EXIT_CODE=0"

if "%~1"=="" goto :cmd_default
if /I "%~1"=="clean" goto :cmd_clean
if /I "%~1"=="generate" goto :cmd_generate
goto :cmd_usage

:cmd_default
call :gen_clean
call :gen_generate
set "EXIT_CODE=%ERRORLEVEL%"
goto :end

:cmd_clean
call :gen_clean
set "EXIT_CODE=%ERRORLEVEL%"
goto :end

:cmd_generate
call :gen_generate
set "EXIT_CODE=%ERRORLEVEL%"
goto :end

:cmd_usage
call :gen_printUsage
set "EXIT_CODE=0"
goto :end

:gen_printUsage
echo usage: generate.bat ^<command^>
echo.
echo Available commands:
echo   clean         Clean build directory
echo   generate      Reorder source and generate pdf
echo.
echo Default commands (no arguments):
echo   clean
echo   generate
exit /b 0

:gen_clean
if exist "%BUILD_DIR%" (
    rmdir /s /q "%BUILD_DIR%"
)
exit /b 0

:gen_generate
python reorder.py
if errorlevel 1 (
    echo [ERROR] reorder.py failed.
    exit /b 1
)

python build.py > contents.tex
if errorlevel 1 (
    echo [ERROR] build.py failed.
    exit /b 1
)

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

xelatex -shell-escape %LATEX_OPTION_QUIET% %LATEX_OPTION% "%FILENAME%.tex" >nul 2>&1
if errorlevel 1 (
    echo [ERROR] xelatex failed. Running verbose build to show errors:
    xelatex -shell-escape %LATEX_OPTION% "%FILENAME%.tex"
    exit /b 1
)

xelatex -shell-escape %LATEX_OPTION_QUIET% %LATEX_OPTION% "%FILENAME%.tex" >nul 2>&1
xelatex -shell-escape %LATEX_OPTION_QUIET% %LATEX_OPTION% "%FILENAME%.tex" >nul 2>&1
move /Y "%BUILD_DIR%\%FILENAME%.pdf" "%FILENAME%.pdf" >nul
echo DONE
exit /b 0

:end
popd
exit /b %EXIT_CODE%
