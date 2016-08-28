# QtCalendar说明文档

计53 王润基

## 支持的功能

* 显示日历界面，并方便地进行日期切换
* 管理事件。事件可重复，可跨天，可删除系列事件中的一个。
* 管理文件。可用鼠标拖入拖出。
* 用户数据的导入导出（暂不支持合并）
* 可固定主界面（暂不支持鼠标穿透）
* 多语言动态切换（目前实现了中英文）

## 使用说明及界面演示

见3张图片

## 内部实现说明

* 自己实现日历界面，不继承QCalendarWidget
* 整体采用Kernel-Shell结构：
  * Kernel：由CalManager类负责处理一切内部逻辑，其指针在各窗口中传递。
  * Shell：各窗口接受用户指令，调用CalManager相应的接口完成功能，并向用户反馈结果。
* 数据存储结构：
  * 事件类CalEvent，笔记类CalNote，文件类CalFile。它们有共同基类CalItem。
  * 它们对Shell只起到传递信息的功能，即由CalManager传出的均为它们的const指针。它们的内容及存储方式由CalManager统一管理。
  * CalManager当前实现方式是按日期索引各项，即`QMap<QString, const CalItem* >`。
  * 配置参数由CalManager中的一个QSettings统一管理。
* 文件存储格式：
  * 对日历信息（CalItem的各子类）：转成JSON保存
  * 对配置信息：由QSettings自动实现文件存取，存成.ini文件
* Qt功能的应用举例：
  * 信号-槽：
    * 各子窗口设置changed()信号，与主窗口的update()绑定。每当子窗口调用CalManager进行修改后，立即发射此信号，各窗口随即刷新显示内容。
  * EventFilter：
    * 实现点击窗口内部拖拽操作的EventFilter。将其注册到任意窗口，即可瞬间实现窗口拖拽功能。

## 可扩展性

* 可继承ICalManager接口，以重载CalManager的实现方式
* 可继承CalItem虚基类，以创建新的项目类型

## 未来的功能

* 用户登陆器
* 对项目中的字符串检索