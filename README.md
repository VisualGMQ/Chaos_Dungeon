# 混乱地牢

用14天写的充满bug的小游戏，采用SDL和OpenGL开发。

**这个分支是专门为Windows开创的，在Windows下使用cmake可以进行编译**

## 如何编译

采用cmake编译，需要SDL2，SDL2_image，SDL2_mixer，glew，glm库。C++和C语言的编译工具为MinGW32的GCC，G++和make(注意是32而不是MinGW64)。

如果你有CMake的GUI版本，那么直接打开GUI版本然后按照常规套路编译就可以。
如果是控制台版本，需要先：

```bash
mkdir build
cd build
```

然后使用CMake产生MinGW Makefile，然后运行make即可：

```bash
cmake -G"MinGW Makefiles" ..
mingw32-make
```

这个时候你会看到build目录下有Chaose_Dungeon可执行文件，将其复制到上层目录，双击即可开始游戏。

## 游戏操作

wsad移动，鼠标左键发射子弹，右键释放炸弹（会炸到自己）

## 游戏截图

![YCEsaj.png](https://s1.ax1x.com/2020/05/04/YCEsaj.png)
![YCErZQ.png](https://s1.ax1x.com/2020/05/04/YCErZQ.png)
