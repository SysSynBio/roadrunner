@echo off
REM Pushes environment variables
setlocal
REM Allows us to properly set and use values of variables inside of if statements/for loops
setlocal EnableDelayedExpansion

REM If they have just cloned the repo, we want to ask them if they want to initialize
REM the directory structure.
REM If they already have the directory structure set up and they are running
REM windows_install from the source folder, we want it to work without reinit'ing everything
REM This can be implemented by checking if there are build*, install*, and source* 
REM folders in the current directory. If so, you can continue building as normal.
REM If not, then check if there are those folders in ..\.. in which case, cd there and
REM start building as normal. If neither of those work, ask if they have just cloned
REM roadrunner and they would like to initialize the directory structure.
if exist "build*" if exist "install*" if exist "source*" goto :init_done
if exist "..\..\build*" if exist "..\..\install*" if exist "..\..\source*" (
  REM Move the current directory to the correct folder
  echo Warning: This script is supposed to be executed from the top of the directory
  echo          structure.
  echo Warning: Changing directory to top of directory structure with `cd ..\..\`
  cd ..\..\
  goto :init_done
)
set INIT=
echo It looks like you have just downloaded roadrunner and you are attempting to install.
set /p INIT="Would you like to create the roadrunner build directory structure? Enter V to see a visualization of what will be created. [Y/N/V]
if "%INIT%"=="Y" (
  REM Temporarily move everything from roadrunner into rr_tmp and then change that to source/roadrunner
  mkdir rr_tmp
  REM Move all files and directories into rr_tmp
  for /D %%f in (*) do if not "%%f"=="%~nx0" move /-Y %%f rr_tmp
  for    %%f in (*) do if not "%%f"=="%~nx0" move /-Y %%f rr_tmp
  copy %~nx0 rr_tmp
  REM Move .git which is hidden
  attrib -h .git
  move .git rr_tmp
  attrib +h rr_tmp\.git
  REM Change the temp folder to its correct folder: source\roadrunner
  mkdir source
  mkdir build_debug
  mkdir install_debug
  move rr_tmp source\roadrunner
  echo Initialization done. Please run this script again with the appropriate arugments.
) else if "%INIT%"=="V" (
  echo <prefix>
  echo ├── build
  echo │   ├── llvm
  echo │   ├── libroadrunner-deps
  echo │   └── roadrunner
  echo ├── install
  echo │   ├── llvm
  echo │   └── roadrunner
  echo └── source
  echo     ├── llvm
  echo     ├── libroadrunner-deps
  echo     └── roadrunner
)
endlocal
exit /B
:init_done

REM Check for debug or release command line flag
REM Check for generator flag (VS201X or Ninja)
REM Set defaults
set ARCH=x64
set BUILD_TESTS=OFF
set GEN_ARCH=
set GEN=
set CONFIG=
set CONF_SUF=
set LLVM_CONFIG_EXECUTABLE=

REM Check for arch flag
REM Check for llvm-config
REM Check for building tests
REM Check for configuration

if "%1"=="" goto usage

:argloop
if not "%1"=="" (
  if "%1"=="--help" goto usage
  if "%1"=="--build-deps" set BUILD_DEPS=ON
  if "%1"=="--build-llvm" set BUILD_LLVM=ON
  if "%1"=="--build-roadrunner" set BUILD_ROADRUNNER=ON
  if "%1"=="--arch" set ARCH=%2
  if !ARCH!==x64 set GEN_ARCH= Win64
  if "%1"=="--build-tests" set BUILD_TESTS=ON
  if "%1"=="--llvm-config" set LLVM_CONFIG_EXECUTABLE=%2
  REM Generator is required
  if "%1"=="--generator" (
    if "%2"=="Ninja"  set GEN=Ninja
    REM                                       Must put no space between the year and arch
    if "%2"=="VS2015" set GEN="Visual Studio 14 2015!GEN_ARCH!"
    if "%2"=="VS2017" set GEN="Visual Studio 15 2017!GEN_ARCH!"
    if "%2"=="VS2019" set GEN="Visual Studio 16 2019!GEN_ARCH!"
  )
  if "%1"=="--config" (
    set CONFIG=%2
    if "!CONFIG!"=="Debug" (
      set CONF_SUF=_debug
    ) else if "!CONFIG!"=="Release" (
      set CONF_SUF=_release
    ) else (
      echo Invalid configuration: "!CONFIG!"
      goto usage
    )
  )
  SHIFT
  GOTO argloop
)

REM Sanity check input
if "%GEN%"=="" (
  echo Error: Must specify a generator
  goto usage
)
if "%CONFIG%"=="" (
  echo Error: Must specify a configuration
  goto usage
)
if not "%BUILD_DEPS%"=="ON" if not "%BUILD_LLVM%"=="ON" if not "%BUILD_ROADRUNNER%"=="ON" (
  echo Error: Must build one of deps, llvm, or roadrunner
  goto usage
)
REM We want them to be able to build LLVM from a source passed in or from the source folder
REM use ..\..\ since this is relative to the build directory
if exist source\llvm set LLVM_SRC=..\..\source\llvm
if "%BUILD_LLVM%"=="ON" if "%LLVM_SRC%"=="" (
  echo Trying to build LLVM, but no source was specified, and there is no source\llvm*
  set /p DOWNLOAD_LLVM="Would you like to download the LLVM source? (Y/N) "
  if "!DOWNLOAD_LLVM!"=="Y" (
    cd source
    git clone https://github.com/llvm-mirror/llvm.git
    cd llvm
    set /p LLVM_VERSION="Which _major_ version (e.g. 6 for 6.0.1) of LLVM would you like to git checkout? "
    git checkout release_!LLVM_VERSION!0
    set LLVM_SRC=!CD!
    cd ..\..\
  ) else (
    goto usage
  )
)
REM Check that there is LLVM installed if we're building roadrunner OR that they
REM passed in the llvm-config path
if "%BUILD_ROADRUNNER%"=="ON" (
  if not exist "install%CONF_SUF%\llvm" (
  if "%LLVM_CONFIG_EXECUTABLE%"=="" (
  goto rr_check_done
  :rr_check_err
  echo Error: Building roadrunner, but there is no LLVM installation 
  echo        and llvm-config was not set
  goto usage
)))
:rr_check_done

REM Set environment variables for MSVC toolchain
REM Use CALL because it is a batch function
REM Check if DevEnvDir is already defined because calling vcvarsall makes path bigger and windows has a maximum path length
if not defined DevEnvDir (
  if "!GEN!"=="Ninja" (
    if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" %ARCH%
    if exist "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" %ARCH%
  )
  if /I "Visual Studio 14" leq "!GEN!" if /I "Visual Studio 15" geq "!GEN!" (
    echo This script does not currently support Visual Studio 2015, but it would
    echo be really easy to add, so just bug @hu-a
    goto usage
  )
  if /I "Visual Studio 15" leq "!GEN!" if /I "Visual Studio 16" geq "!GEN!" (
    call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" %ARCH%
  )
  if /I "Visual Studio 16" leq "!GEN!" if /I "Visual Studio 17" geq "!GEN!" (
    call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" %ARCH%
  )
  
)
REM @echo on

REM Check that they have the appropriate tools installed
cmake --version
if errorlevel 9009 (
  echo Could not find cmake executable, exiting
  goto usage
)
if %GEN%==Ninja (
  ninja --version
  if errorlevel 9009 (
    echo Generator was set to Ninja but Ninja was not found
    goto usage
  )
) else (
  REM We should be able to invoke cl because we used vcvarsall earlier
  cl
  if errorlevel 9009 (
    echo Generator was set to MSVC but cl.exe was not found
    goto usage
  )
)

REM If they want to build deps
if "%BUILD_DEPS%"=="ON" (
  if not exist source\libroadrunner-deps (
    echo It looks like you do not have the source for libroadrunner-deps in the source folder
:download_deps
    set /p DOWNLOAD_DEPS="Do you want to (D)ownload the sources, give a (P)ath to a folder with the sources, or (Q)uit? [D/P/Q]
    if "!DOWNLOAD_DEPS!"=="D" (
      cd source
      echo Cloning...
      git clone https://github.com/sys-bio/libroadrunner-deps.git
      cd ..
    ) else if "!DOWNLOAD_DEPS!"=="P" (
      set /p DEPS_PATH="Enter the path: "
      copy !DEPS_PATH! source\roadrunner
      REM FIXME Check for error or valid path
    ) else if "!DOWNLOAD_DEPS!"=="Q" (
      echo Quitting.
      exit /B
    ) else (
      echo Invalid input.
      goto :download_deps
    )
  )
  REM Set up libroadrunner-deps
  mkdir build%CONF_SUF%\libroadrunner-deps\
  cd build%CONF_SUF%\libroadrunner-deps\
  REM Use the && ^ to execute the next line only if this line succeeds
  cmake -G %GEN% -DCMAKE_INSTALL_PREFIX=..\..\install%CONF_SUF%\roadrunner ..\..\source\libroadrunner-deps && cmake --build . --config %CONFIG% --target install
  REM Exit if there was a failure in the build stage
  if %errorlevel% neq 0 (
    echo Could not build and install libroadrunner-deps
    cd ..\..\
    endlocal
    REM Only exit the script, not cmd.exe
    exit /B
  )
  cd ..\..\
)

REM If they want to build LLVM from source
if "%BUILD_LLVM%"=="ON" (
  if "%LLVM_SRC%"=="" (
    echo Trying to build LLVM, but no LLVM source was found
    goto usage
  )
  mkdir build%CONF_SUF%\llvm\
  cd build%CONF_SUF%\llvm\

  cmake -G %GEN% -DCMAKE_INSTALL_PREFIX=..\..\install%CONF_SUF%\llvm -DLLVM_TARGETS_TO_BUILD=X86 %LLVM_SRC% && cmake --build . --config %CONFIG% --target install

  if %errorlevel% neq 0 (
    echo Could not build and install LLVM
    endlocal
    REM Only exit the script, not cmd.exe
    exit /B
  )
  cd ..\..\
)


if "%BUILD_ROADRUNNER%"=="ON" (
  mkdir build%CONF_SUF%\roadrunner
  cd build%CONF_SUF%\roadrunner

  cmake -G %GEN% -DTHIRD_PARTY_INSTALL_FOLDER=..\..\install%CONF_SUF%\roadrunner -DCMAKE_INSTALL_PREFIX=..\..\install%CONF_SUF%\roadrunner -DLLVM_CONFIG_EXECUTABLE=%LLVM_CONFIG_EXECUTABLE% -DBUILD_TESTS=%BUILD_TESTS% -DBUILD_TEST_TOOLS=%BUILD_TESTS% ..\..\source\roadrunner && cmake --build . --config %CONFIG% --target install

  if %errorlevel% neq 0 (
    echo Could not build and install roadrunner
    cd ..\..\
    endlocal
    exit /B
  )
  cd ..\..\
  echo Finished building and installing roadrunner
)

echo Build and install complete.
endlocal
exit /B

:usage
  echo Usage
  echo --build-deps
  echo --build-llvm
  echo --build-roadrunner
  echo --arch [x64, x86]                             (Defaults to x64)
  echo --build-tests
  echo --llvm-src    path/to/llvm.src                (Use if you are building LLVM)
  echo --llvm-config path/to/llvm-config.exe         (Use if LLVM is already built)
  echo --llvm-version [6.0.1]
  echo --generator [Ninja, VS2015, VS2017, VS2019]   (Required)
  echo --config [Debug, Release]                     (Required)
  endlocal
  exit /B 0