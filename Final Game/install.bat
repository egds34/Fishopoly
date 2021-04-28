@echo off
goto check_Permissions

:check_Permissions
    echo Administrative permissions required. Detecting permissions...

    net session >nul 2>&1
    if %errorLevel% == 0 (
        setx MAGICK_CODER_MODULE_PATH "%CD%\modules\coders" 
    ) else (
        echo Failure: Please run as administrator.
		pause
    )
