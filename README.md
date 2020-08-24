# QHot

[![Travis Build Status](https://travis-ci.org/patrickelectric/qhot.svg?branch=master)](https://travis-ci.org/patrickelectric/qhot)
[![Build status](https://ci.appveyor.com/api/projects/status/jpvs6sld54hfbon1/branch/master?svg=true)](https://ci.appveyor.com/project/patrickelectric/qhot/branch/master)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/patrickelectric/qhot.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/patrickelectric/qhot/context:cpp)

Live preview of your qml modifications !
It works with nested qml components !

Check the online version [qmlonline](http://qmlonline.kde.org/) (Now as an official KDE project) !

## Downloads :package:

- :computer: [Windows](https://github.com/patrickelectric/qhot/releases/download/continuous/qhot_release.zip)
- :apple: [MacOS](https://github.com/patrickelectric/qhot/releases/download/continuous/qhot.dmg)
- :penguin: [Linux](https://github.com/patrickelectric/qhot/releases/download/continuous/qhot.AppImage)

## Install :zap:
- Arch [AUR]: `qhot-git`

#### How to use
`./qhot.exe myFile.qml` or `./qhot.dmg myFile.qml` or `./qhot.AppImage myFile.qml`

![](/doc/example.gif)

##### Supported commands:
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
```
