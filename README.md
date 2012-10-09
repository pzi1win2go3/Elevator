项目：
		电梯模拟器系统设计与实现
——————————————————————————————————————————————————
成员：
		赵天雨(1100012957)
    郑淇木(1100012849) 
    崔逸卿(1100012950)
——————————————————————————————————————————————————
说明：

		-!!!!!!!!!!!!!!!!-
		-!!! 请随时修改 !!!-
		-!!!!!!!!!!!!!!!!-

		1.命名规则：
			(1)类首字母大写
			(2)函数首字母小写
			(3)常量全大写
			(4)驼峰法
			(5)含义清楚

		2.类声明放在.h文件中，类实现放在.cpp文件中。

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
						start
						end
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
					Functions:
						action()
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


		
