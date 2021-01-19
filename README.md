# QHot

[![Travis Build Status](https://travis-ci.org/patrickelectric/qhot.svg?branch=master)](https://travis-ci.org/patrickelectric/qhot)
[![Build status](https://ci.appveyor.com/api/projects/status/jpvs6sld54hfbon1/branch/master?svg=true)](https://ci.appveyor.com/project/patrickelectric/qhot/branch/master)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/patrickelectric/qhot.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/patrickelectric/qhot/context:cpp)

Live preview of your qml modifications. It works with nested qml components !

Check the online version [qmlonline](http://qmlonline.kde.org/) (Now as an official KDE project) !

## Install

### Downloads :package:

- :computer: [Windows](https://github.com/patrickelectric/qhot/releases/download/continuous/qhot_release.zip)
- :apple: [MacOS](https://github.com/patrickelectric/qhot/releases/download/continuous/qhot.dmg)
- :penguin: [Linux](https://github.com/patrickelectric/qhot/releases/download/continuous/qhot.AppImage)

### Arch Linux :zap:

- AUR: `qhot-git`

### Build for local Qt kit

Build qhot from sources for your specific Qt kit, and install it alongside the
other Qt tools. This way qhot will find all the Qt plugins that you already
have installed on your local system. No need for a large package.

```powershell
PS git clone https://github.com/patrickelectric/qhot.git
PS cd qhot
PS md my-build
# QTDIR should point to a Qt kit, e.g. C:/Qt/5.15.2/msvc2019_64
PS cmake -S . -B my-build -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="$Env:QTDIR"
PS cmake --build my-build
# Install qhot in the bin folder, e.g. C:/Qt/5.15.2/msvc2019_64/bin
PS cmake --build my-build --target install
```

## How to use

To run qhot:  
  `./qhot.exe myFile.qml` or `./qhot.dmg myFile.qml` or `./qhot.AppImage myFile.qml`

![example](/doc/example.gif)

### Supported commands

```sh
--help, -h, -?           Give this friendly help message for our confort
--desktop                Force use of desktop GL (AA_UseDesktopOpenGL)
--gles                   Force use of GLES (AA_UseOpenGLES)
--software               Force use of software rendering (Qt::AA_UseSoftwareOpenGL)
--scaling                Enable High DPI scaling (AA_EnableHighDpiScaling)
--no-scaling             Disable High DPI scaling (AA_DisableHighDpiScaling)
--import-path, -I        Add list of **import** paths (path:path)
--plugin-path, -P        Add list of **plugin** paths (path:path)
--translation            Set the translation file (file)
--style                  Change style
--profile-path           Path (including filename) to qhot-profile.json (file)
--background             Set the background color (color)
--quick-controls-conf    Path (including filename) to qtquickcontrols2.conf (file)
```

### Store options in a profile

All the command line options can also be set in a ```qhot-profile.json``` file. For
example:

```json
{
    "import-path": [
        "lib/qml/modules",
        "src/qml"
    ],
    "background": "#808080",
    "quick-controls-conf": "src/qml/qtquickcontrols2.conf"
}
```

The import paths in the example above are relative to the file itself, but can
also be absolute. The relative paths make it more convenient to add it to a
vcs repository.

### Integrate in QtCreator

Integrating qhot in QtCreator makes it very easy to quickly prototype within
the IDE. See [Using External Tools](https://doc.qt.io/qtcreator/creator-editor-external.html).
Example configuration:

1. Executable: ```C:\Qt\5.15.2\msvc2019_64\bin\qhot.exe```
2. Arguments: ```%{CurrentDocument:FilePath} --profile-path
"%{ActiveProject:Path}/qhot-profile.json"```
3. Environment: ```QT_ASSUME_STDERR_HAS_CONSOLE=1``` (This will append stdout
to the console)

It is also quite handy to add a shortcut in QtCreator to launch qhot. See
[Keyboard Shortcuts](https://doc.qt.io/qtcreator/creator-keyboard-shortcuts.html).

### Shortcuts

- **F1** Launch popup to change background and control sizing behaviour
- **F2** Toggles visibility: maximized, full screen, back to default
- **Ctrl+Q** Quit application

### Loading Test Data

QHot has the same functionality as qmlscene to load dummy test data and it
works exactly the same way:
[load test data](https://doc.qt.io/qt-5/qtquick-qmlscene.html#loading-test-data).