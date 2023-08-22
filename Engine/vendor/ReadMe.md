# 添加额外依赖库的方法

通过`git add submodule url path`的方式就可以把另一个git项目作为库文件添加到项目里了，具体例子就是：

`git add https://github.com/nothings/stb.git Engine/vendor/stb`

就可以把stb这个项目添加到库里了，注意一下，这里添加的库会直接把目标项目main分支的最新的提交点作为下载点，也就是之后都会用这个commit来作为库文件了。

如果要更新的话，现在先不写，要更新库文件的时候再做，在写。