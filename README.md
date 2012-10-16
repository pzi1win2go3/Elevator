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
			M: 	class Time 
					class Mission 
					class Elevator
			
			V: 	void print()
					void info()     // in ElevatorController

			C: 	class ElevatorController

		4.图形输出采用 ASCII

		5.算法：
			(1)先到先服务		 	FCFS
			(2)最短寻找时间 	SSTF

		6.main函数内容：
			(1)输入
			(2)以 信息更新周期(DURATION) 为周期的循环：
				a.产生任务
				b.电梯调度

		7.数据结构：
			1. 具体算法中对 Mission 和 Elevator 都使用指针
			2. Elevator 通用，故放在 C 的基类中
			3. Mission 因算法不同而变化，故放在 C 的子类中

		8.类的设计：
			(1)
				class Time:
			(2)
				class Mission:
			(3)
				class Elevator:
				
			(4)-----------IMPORTANT------------
				class ElevatorController:
					variables: 
						1. capacity, storey, elevatorNum, DURATION
						2. elevator, waiting
						3. maxWaitingTime, aveWaitingTime, aveWaitingTimeCount, aveFlow, totalFlow
						4. globalClock
					functions:
						1. show(), info()
						2. updateMaxWaitingTime(), updateAveWaitingTime(), updateAveFlow()

				(4).a
					class FCFSController < ElevatorController
						variables:
							1. queue<Mission *> MissionQ
						functions:
							1. control()
							2. storeMission()

				(4).b
					class SSTFController < ElevatorController
						variables:
							1. vector<Mission *> MissionList
						functions:
							1. control()
							2. storeMission()
				----------------------------------

		9.全局变量：

		10.新想法：
		
