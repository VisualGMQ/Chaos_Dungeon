# 混乱地牢

用14天写的充满bug的小游戏，采用SDL和OpenGL开发。

## 如何编译

如果你是Windows系统，请前往`windows_verion`分支，那里有windows下的编译方式和工程。

如果你是MacOS或Linux，看这个就够了。

采用cmake编译，需要SDL2，SDL2_image，SDL2_mixer，glew，glm库。如果有了，请直接

```bash
mkdir build
cd build
cmake ..
make
make install
cd ..
```

这个时候你会看到Chaose_Dungeon文件夹，执行`./Chaose_Dungeon/Chaose_Dungeon`即可运行。

## 游戏操作

wsad移动，鼠标左键发射子弹，右键释放炸弹（会炸到自己）

## 游戏截图

![YCEsaj.png](https://s1.ax1x.com/2020/05/04/YCEsaj.png)
![YCErZQ.png](https://s1.ax1x.com/2020/05/04/YCErZQ.png)
