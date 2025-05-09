#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int RECT_WIDTH = 100;
const int RECT_HEIGHT = 100;
const int RECT_SPEED = 5;

int main() {
    // 初始化随机数种子
    srand(time(NULL));

    // 初始化GLFW库
    if (!glfwInit())
        return -1;

    // 设置窗口提示值
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); // 无边框
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // 无法改变大小
    glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE); // 无法获取焦点
    glfwWindowHint(GLFW_FLOATING, GLFW_FALSE); // 无法接收输入事件

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
    glfwSwapInterval(1);

    // 初始化矩形位置
    int rectX = (WINDOW_WIDTH - RECT_WIDTH) / 2;
    int rectY = (WINDOW_HEIGHT - RECT_HEIGHT) / 2;

    // 初始化矩形速度
    int speedX = RECT_SPEED * (rand() % 2 == 0 ? -1 : 1);
    int speedY = RECT_SPEED * (rand() % 2 == 0 ? -1 : 1);

    // 初始化矩形颜色
    float colorR = (float)rand() / RAND_MAX;
    float colorG = (float)rand() / RAND_MAX;
    float colorB = (float)rand() / RAND_MAX;

    // 定义要显示的文字
    std::string text = "Hello, World!";

    // 主循环
    while (!glfwWindowShouldClose(window)) {
        // 处理事件
        glfwPollEvents();

        // 更新矩形位置
        rectX += speedX;
        rectY += speedY;

        // 检测边界碰撞
        if (rectX <= 0 || rectX + RECT_WIDTH >= WINDOW_WIDTH) {
            speedX = -speedX; // 反向移动
            colorR = (float)rand() / RAND_MAX; // 随机颜色
        }
        if (rectY <= 0 || rectY + RECT_HEIGHT >= WINDOW_HEIGHT) {
            speedY = -speedY; // 反向移动
            colorG = (float)rand() / RAND_MAX; // 随机颜色
        }

        // 清除颜色缓冲区
        glClear(GL_COLOR_BUFFER_BIT);

        // 设置文字颜色
        glColor3f(colorR, colorG, colorB);

        // 设置文字位置
        int textX = rectX + RECT_WIDTH / 2;
        int textY = rectY + RECT_HEIGHT / 2;

        // 设置文字大小
        int fontSize = 24;
        void* font = GLUT_BITMAP_HELVETICA_12;

        // 绘制文字
        glRasterPos2f(2.0f * textX / WINDOW_WIDTH - 1.0f, 2.0f * textY / WINDOW_HEIGHT - 1.0f);
        for (char c : text) {
            glutBitmapCharacter(font, c);
        }

        // 交换缓冲区
        glfwSwapBuffers(window);
    }

    // 销毁窗口
    glfwDestroyWindow(window);

    // 终止GLFW库
    glfwTerminate();

    return 0;
}

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int POINT_SIZE = 5;
const int POINT_SPEED = 5;

int main() {
    // 初始化随机数种子
    srand(time(NULL));

    // 初始化GLFW库
    if (!glfwInit())
        return -1;

    // 设置窗口提示值
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); // 无边框
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // 无法改变大小
    glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE); // 无法获取焦点
    glfwWindowHint(GLFW_FLOATING, GLFW_FALSE); // 无法接收输入事件

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
    glfwSwapInterval(1);

    // 初始化点位置
    int pointX = WINDOW_WIDTH / 2;
    int pointY = WINDOW_HEIGHT / 2;

    // 初始化点速度
    int speedX = POINT_SPEED * (rand() % 2 == 0 ? -1 : 1);
    int speedY = POINT_SPEED * (rand() % 2 == 0 ? -1 : 1);

    // 初始化点颜色
    float colorR = (float)rand() / RAND_MAX;
    float colorG = (float)rand() / RAND_MAX;
    float colorB = (float)rand() / RAND_MAX;

    // 主循环
    while (!glfwWindowShouldClose(window)) {
        // 处理事件
        glfwPollEvents();

        // 更新点位置
        pointX += speedX;
        pointY += speedY;

        // 检测边界碰撞
        if (pointX <= 0 || pointX >= WINDOW_WIDTH) {
            speedX = -speedX; // 反向移动
            colorR = (float)rand() / RAND_MAX; // 随机颜色
        }
        if (pointY <= 0 || pointY >= WINDOW_HEIGHT) {
            speedY = -speedY; // 反向移动
            colorG = (float)rand() / RAND_MAX; // 随机颜色
        }

        // 清除颜色缓冲区
        glClear(GL_COLOR_BUFFER_BIT);

        // 设置点颜色
        glColor3f(colorR, colorG, colorB);

        // 绘制点
        glPointSize(POINT_SIZE);
        glBegin(GL_POINTS);
        glVertex2f(2.0f * pointX / WINDOW_WIDTH - 1.0f, 2.0f * pointY / WINDOW_HEIGHT - 1.0f);
        glEnd();

        // 交换缓冲区
        glfwSwapBuffers(window);
    }

    // 销毁窗口
    glfwDestroyWindow(window);

    // 终止GLFW库
    glfwTerminate();

    return 0;
}
