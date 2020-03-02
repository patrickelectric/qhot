# QHot

[![Travis Build Status](https://travis-ci.org/patrickelectric/qhot.svg?branch=master)](https://travis-ci.org/patrickelectric/qhot)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/patrickelectric/qhot.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/patrickelectric/qhot/context:cpp)
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2Fpatrickelectric%2Fqhot.svg?type=shield)](https://app.fossa.io/projects/git%2Bgithub.com%2Fpatrickelectric%2Fqhot?ref=badge_shield)

Live preview of your qml modifications !
It works with nested qml components !

Check the online version [qmlonline](https://patrickelectric.work/qmlonline/) !

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
```


## License
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2Fpatrickelectric%2Fqhot.svg?type=large)](https://app.fossa.io/projects/git%2Bgithub.com%2Fpatrickelectric%2Fqhot?ref=badge_large)