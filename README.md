# 记录一下自己第一次使用cmake构建项目的过程
## 问题
### 1.vscode的配置文件，task.json和launch.json为什么有时候无法生效？
    VScode对于文件目录十分敏感，必须必须保证两件事才能使得task.json和launch.json，  
   1. 首先，task.json和launch.json必须在.vscode这个目录下。
   2. 其次，VScode左侧的文件列表中，.vscode必须是第一级子目录。
      1. 如果你通过vscode左上角的文件->打开文件夹->(点击自己的项目文件夹，假设名字为test)之后，.vscode必须在test之下。
   3. 通过以上操作即可通过ctrl+shift+b运行task.json中的默认任务，或者按下F5运行launch.json中的默认任务。也可以通过按下ctrl+shift+p呼出上方的菜单栏，点击下方的运行任务（Run Task）之后，里面会显示你在task.json中定义的任务名，点击任务对应的任务名即可进行操作。
### 2.使用CmakeLiists进行文件构建具体需要修改什么？
    见注释
### 3.task.json文件的作用和launch.json的作用见注释
#### 想必是极好的