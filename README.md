# EIE3105

All material from 3105 is recorded.
The content is for learning purposes only, please do not use it directly, the consequences of being found are serious

上傳時遇到文件太大無法上傳問題，故使用了Git LFS

以下為設置過程
执行 git lfs install 开启lfs功能
使用 git lfs track 命令进行大文件追踪 例如git lfs track "*.png" 追踪所有后缀为png的文件
使用 git lfs track 查看现有的文件追踪模式
提交代码需要将gitattributes文件提交至仓库. 它保存了文件的追踪记录
提交后运行git lfs ls-files 可以显示当前跟踪的文件列表
将代码 push 到远程仓库后，LFS 跟踪的文件会以『Git LFS』的形式显示:
clone 时 使用'git clone' 或 git lfs clone均可

作者：amosbake
链接：https://www.jianshu.com/p/493b81544f80
来源：简书
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
