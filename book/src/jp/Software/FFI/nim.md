# Nim

[autd3_sim](https://github.com/shinolab/autd3_nim)はNimに対応したラッパーを提供している.

## Installation

nimbleでインストールできる.

```
requires "https://github.com/shinolab/autd3_nim.git == 2.2.2"
```

## Usage

基本的には, C++版と同じになるように設計している.

たとえば, [Getting Started](../Users_Manual/getting_started.md)と等価なコードは以下のようになる.

```nim
import strformat
import strutils

import autd3
import autd3/soem

import tests/runner

proc onLost(msg: cstring) =
    echo msg
    quit(-1)

proc getInterface(): string =
    try:
        let adapters = SOEM.enumerateAdapters
        for i, adater in adapters:
            echo fmt"[{i}]: {adater.desc}, {adater.name}"

        stdout.write "Choose adapter: "
        let i = stdin.readLine.parseInt
        adapters[i].name
    except:
        ""

when isMainModule:
    try:
        var cnt = initController()
        cnt.addDevice([0.0, 0.0, 0.0], [0.0, 0.0, 0.0])

        let ifname = getInterface()
        let link = initSOEM(ifname, cnt.deviceNum(), 1, onLost, true)
        if not cnt.open(link):
            echo Controller.lastError
            quit(-1)

        cnt.checkTrials = 50

        cnt.clear()
        cnt.synchronize()

        let firmList = cnt.firmwareInfoList()
        for firm in firmList:
            echo firm

        let config = initSilencerConfig()
        cnt.send(config)

        let f = initFocus([90.0, 80.0, 150.0])
        let m = initSine(150)

        cnt.send(m, f)

        discard stdin.readLine

        cnt.close()

    except:
        let
            e = getCurrentException()
            msg = getCurrentExceptionMsg()
        echo "Got exception ", repr(e), " with message ", msg

```

より詳細なサンプルは[example](https://github.com/shinolab/autd3_nim/tree/master/examples)を参照されたい.

その他, 質問があれば[GitHubのissue](https://github.com/shinolab/autd3_nim/issues)にてお願いします.
