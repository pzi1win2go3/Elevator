项目：
	电梯模拟器系统设计与实现

成员：
	赵天雨(1100012957)
	郑淇木(1100012849) 
	崔逸卿(1100012950)

说明：

		-!!! 请随时修改 !!!-

		1.风格：
			(1)命名规则：
				a.类首字母大写
				b.函数首字母小写
				c.常量全大写
				d.驼峰法
				e.含义清楚
			(2)注意缩进和上下对齐

		2.项目目录结构：
			(个人意见)
			/Include: 		.h文件(类声明放在.h文件中)
			/Source:  		.cpp文件(类实现放在.cpp文件中)
			/Resource:		可能会用到的图片等资源
			/Help:				帮助文档
			.gitignore 		描述 git commit 时自动忽略的文件类型
			main.cpp 			主函数
			README.md 		说明文档

		3.考虑整体使用 MVC 的概念构建项目：
			M: class Time, class Mission, class Elevator
			V: void Print()
			C: class ElevatorController

		4.图形输出采用库 easyX

		5.算法：
			(1)先到先服务

		6.main函数内容：
			(1)输入
			(2)以 信息更新周期 为周期的循环：
				a.产生任务
				b.电梯调度

		7.数据结构：

		8.类的设计：
			(1)
				class Time:
			(2)
				class Mission:
					Variables:
						from
						to
						passenger
			(3)
				class Elevator:
					Variables:
						Mission *
						//passenger
						position
						destination
						status
						id
						destination
					Functions:
						move()
						takeMission()
						complete()
						open()
						close()
			(4)
				class ElevatorController:
					Variables:
						queue<Mission> //maybe other DS
						Elevator *
					Function:
						control //put algorithm here

		9.全局变量：

		10.新想法：
			a.初始化变量命名使用前缀 init
			b.Elevator 的函数只包括其一步一步的动作，具体动作如何组合不使用 Elevator::action(), 而是放到 controller 里面实现。
		
