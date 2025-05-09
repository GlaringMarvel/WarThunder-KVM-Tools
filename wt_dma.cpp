#include "wt_dma.h"

int main(int argc, char *argv[])
{
	//检查当前程序是否以root权限运行，如果不是，则打印错误信息并退出
	if(geteuid() != 0)
	{
		printf("[Error] %s is not running as root\n", argv[0]);
		return 0;
	}

	//定义一个常量字符串，表示War Thunder的进程名
	const char* wt_proc_name = "aces.exe";

	std::cout << "Time Wait 5 s" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));

	// 初始化随机数种子
	srand(time(NULL));
	// 初始化GLFW库
	if (!glfwInit())
		return -1;
	// 初始化GLUT库
	glutInit(&argc, argv);
	// 设置窗口提示值
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); // 无边框
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // 无法改变大小
	glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
	glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE); // 无法获取焦点
	glfwWindowHint(GLFW_FLOATING, GLFW_FALSE); // 无法接收输入事件
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE); // 支持帧缓冲区透明度
	// 创建窗口
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Window", glfwGetPrimaryMonitor(), NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwFocusWindow(window);
	// 设置窗口位置
	int screenWidth, screenHeight;
	glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), NULL, NULL, &screenWidth, &screenHeight);
	int windowX = (screenWidth - WINDOW_WIDTH) / 2;
	int windowY = (screenHeight - WINDOW_HEIGHT) / 2;
	glfwSetWindowPos(window, windowX, windowY);
	// 设置窗口透明度
	glfwSetWindowOpacity(window, 1.0f);
	// 设置当前上下文
	glfwMakeContextCurrent(window);
	// 设置交换间隔

	//当程序处于激活状态时，循环执行以下操作
	while(active)
	{
		//如果wt的内存状态不是已找到并准备好，则执行以下操作
		if(wt_mem.get_proc_status() != process_status::FOUND_READY)
		{
			//打印警告信息，表示正在寻找War Thunder的进程
			printf("[Warn]Searching for War Thunder......\n");

			//尝试打开wt的进程
			wt_mem.open_proc(wt_proc_name);

			//如果wt的内存状态变为已找到并准备好，则执行以下操作
			if(wt_mem.get_proc_status() == process_status::FOUND_READY)
			{
				//获取aces.exe的基址，并打印出来
				aces_base = wt_mem.GetModuleAddress("aces.exe","aces.exe");
				printf("Found War Thunder!\n");
				printf("[Info]aces.exe Base: %lx\n", aces_base);

				int i =0;
				while (true)
				{
					// 处理事件
					glfwPollEvents();
					// 清除颜色缓冲区
					glClear(GL_COLOR_BUFFER_BIT);

					for (i = 0; i < 40; i++)
					//for (int i = 1; i < 8; i = 1)
					{	
						// 获得玩家矩阵
						ViewMatrix(aces_base, matrix);
						// 本地玩家
						int localplayer = 1;
						// 获取玩家数据
						PlayerValues local_player = playerValues(aces_base, 0 ,localplayer);
						// 获取玩家团队
						//uint32_t player_team = local_player.team;
						//std::cout << "PlayerTeam:" << player_team << std::endl;

						//获取其他玩家数据
						localplayer = 0;
						PlayerValues player_data = playerValues(aces_base, i ,localplayer);
						// 如果为敌方玩家
						if(local_player.team != player_data.team && player_data.state ==0 && player_data.team != 0)
						{
							View origin =  WorldtoScreen(matrix, player_data, WINDOW_WIDTH, WINDOW_HEIGHT);

							View draw = DrawOverWatch(origin);
							// 定义要显示的文字
							std::string vehicle_id = player_data.vehicle_id;

							//std::cout << "PlayerID:" << player_data.play_id << std::endl;
							//std::cout << "VehicleID:" << vehicle_id << std::endl;
							//std::cout << "X:" << player_data.player_x << " Y:" << player_data.player_y << " Z:" << player_data.player_x << std::endl;
							//std::cout << "ScreenX:" << draw.draw_x << " ScreenY:" << draw.draw_y << std::endl;
							// 计算距离
							std::string distance;
							float distanceF;
							Distance(local_player, player_data, &distance, &distanceF);
							//std::string distance = Distance(local_player, player_data);
							//std::cout << "Distance:" << distance << std::endl;

							// 无敌判断
							std::string protect;
							std::ostringstream st;
							st << std::fixed << std::setprecision(1) << player_data.super_time;
							std::string super_time = st.str();
							if (player_data.protect == 1)
							{
								protect = " Protect : " + super_time + " s";
								//std::cout << "Protect:" << super_time << std::endl;
							}
							else{protect = " ";}

							// 装填指示
							std::string reload;
							if (player_data.reload > 0)
							{reload = std::to_string(player_data.reload/3);}
							else
							{reload = " ";}
							// 拼接字符串
							std::string enemy_info = vehicle_id + " [ " + distance + " Km] " + protect;
							std::string overwatch = " [ " + distance + " Km] ";
							// 设置文字位置
							//int textX = draw.draw_x;
							//int textY = (1080 - draw.draw_y);

							// 设置文字颜色
							Color text_color = color(distanceF, local_player.vehicle_type, player_data.vehicle_type);
							glColor3f(text_color.R, text_color.G, text_color.B);
							// 设置文字大小
							//int fontSize = 128;

							//View point[8];
							View* point = DrawBox(player_data, matrix, WINDOW_WIDTH, WINDOW_HEIGHT);
							for (int i = 0; i < 4; i++) 
							{
								point[i] = point[i];
							}

							// 绘制点
							for (int i = 0; i < 4; i++) 
							{
								glPointSize(POINT_SIZE);
								glBegin(GL_POINTS);
								glVertex2f(2.0f * point[i].draw_x / WINDOW_WIDTH - 1.0f, 
										2.0f * (1080 - point[i].draw_y) / WINDOW_HEIGHT - 1.0f);
								// std::cout << "point[i].draw_x" << point[i].draw_x << std::endl;
								// std::cout << "point[i].draw_y" << point[i].draw_y << std::endl;
								glEnd();
							}

							// 绘制信息
							glRasterPos2f(2.0f * point[0].draw_x / WINDOW_WIDTH - 1.0f, 
										2.0f * (1080 - point[0].draw_y + 10) / WINDOW_HEIGHT - 1.0f);
							for (char c : enemy_info) 
							{
								glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
							}
							// 绘制玩家ID
							glRasterPos2f(2.0f * point[0].draw_x / WINDOW_WIDTH - 1.0f, 
										2.0f * (1080 - point[0].draw_y + 35) / WINDOW_HEIGHT - 1.0f);
							for (char c : player_data.play_id) 
							{
								glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
							}
							// 绘制装填时间
							glRasterPos2f(2.0f * (point[3].draw_x + 5) / WINDOW_WIDTH - 1.0f, 
										2.0f * (1080 - point[3].draw_y) / WINDOW_HEIGHT - 1.0f);
							for (char c : reload) 
							{
								glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
							}
							// 超视野绘制
							glRasterPos2f(2.0f * draw.draw_x / WINDOW_WIDTH - 1.0f, 
										2.0f * (1080 - draw.draw_y) / WINDOW_HEIGHT - 1.0f);
							for (char c : overwatch) 
							{
								glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
							}
							/*
							GLUT_BITMAP_8_BY_13: 字符大小为8x13像素。
							GLUT_BITMAP_9_BY_15: 字符大小为9x15像素。
							GLUT_BITMAP_TIMES_ROMAN_10: Times Roman字体，字符大小为10像素。
							GLUT_BITMAP_TIMES_ROMAN_24: Times Roman字体，字符大小为24像素。
							GLUT_BITMAP_HELVETICA_10: Helvetica字体，字符大小为10像素。
							GLUT_BITMAP_HELVETICA_12: Helvetica字体，字符大小为12像素。
							GLUT_BITMAP_HELVETICA_18: Helvetica字体，字符大小为18像素。
							*/
							//std::this_thread::sleep_for(std::chrono::seconds(1));
						}
					}
					// 交换缓冲区
					glfwSwapBuffers(window);
					i = 0;
				}
			}
		}
		//如果wt的内存状态是已找到并准备好，则检查进程是否仍然存在
		else
		{
			wt_mem.check_proc();
		}
		//每隔10毫秒执行一次
		//std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	// 销毁窗口
	glfwDestroyWindow(window);
	// 终止GLFW库
	glfwTerminate();
	return 0;
}
