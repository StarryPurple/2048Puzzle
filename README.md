### 2048 Puzzle

前端部分需要`Crow`库与`Asio`库。已经放在`third_party`中，你也可以下载别的版本。

1. 实现并提交`src/game_logic.cpp`.
2. 实现并提交`src/user_logic.cpp`.

我们提供了一个模拟游戏的服务程序（大部分是Gemini写的）。
在完成任务1后，你可以运行`server`，保持其运行，并在`web`文件夹里运行
```
python3 -m http.server 8000
```
以启动一个Web服务器。
保持其运行，在浏览器里访问 `http://localhost:8000/` 以手动模拟游戏。
