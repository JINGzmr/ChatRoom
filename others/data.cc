#include "data.h"

#include <unistd.h>
#include <termios.h>
#include <iostream>
using namespace std;

string chatname = "";
string chatgroup = "";

string produce_id(void)
{
    time_t timestamp;
    time(&timestamp);
    string id = to_string(timestamp);
    return id;
}

string getInputWithoutCtrlD()
{
    struct termios oldt, newt;

    // 获取当前终端模式
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // 禁用 ECHO 和 ICANON 标志
    newt.c_lflag &= ~(ICANON | ECHO);

    // 设置新终端模式
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    std::string input;
    char ch;
    while (std::cin.get(ch))
    {
        if (ch == '\x04')
        { // Ctrl+D
          // 不做任何响应
        }
        else if (ch == '\n')
        {
            cout << ch;
            break; // 回车表示输入结束
        }
        else if (ch == 27)
        { // Esc
            cout << "esc" << endl;
            return "esc";
        }
        else if (ch == 127)
        { // Backspace
            if (!input.empty())
            {
                input.pop_back();
                cout << "\b \b"; // 清除前一个字符并移动光标
            }
        }
        else
        {
            cout << ch; // 输出字符到终端
            input += ch;
        }
    }

    // 恢复原始终端模式
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    // 检查输入是否包含空格
    if (input.find(' ') != std::string::npos)
    {
        cout << "\033[31m警告：输入不能包含空格，请重新输入\033[0m\n"; // 红色告示
        return "";                                                     // 返回一个空字符串表示输入无效
    }

    return input;
}

// 密码加密显示
string withoutdisplay()
{
    struct termios oldt, newt;

    // 获取当前终端模式
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // 禁用 ECHO 和 ICANON 标志
    newt.c_lflag &= ~(ICANON | ECHO);

    // 设置新终端模式
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    std::string input;
    char ch;
    while (std::cin.get(ch))
    {
        if (ch == '\x04')
        { // Ctrl+D
          // 不做任何响应
        }
        else if (ch == '\n')
        {
            cout << ch;
            break; // 回车表示输入结束
        }
        else if (ch == 27)
        { // Esc
            cout << "esc" << endl;
            return "esc";
        }
        else if (ch == 127)
        { // Backspace
            if (!input.empty())
            {
                input.pop_back();
                cout << "\b \b"; // 清除前一个字符并移动光标
            }
        }
        else
        {
            cout << "*"; // 输出加密字符到终端
            input += ch;
        }
    }

    // 恢复原始终端模式
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    // 检查输入是否包含空格
    if (input.find(' ') != std::string::npos)
    {
        cout << "\033[31m警告：输入不能包含空格，请重新输入\033[0m\n"; // 红色告示
        return "";                                                     // 返回一个空字符串表示输入无效
    }

    return input;
}

// 检测是否为非法输入的函数
int checkcin(const string &str)
{
    try
    {
        size_t pos;
        int result = stoi(str, &pos);

        // 确保整个字符串都被转换
        if (pos == str.length())
        {
            return result;
        }
        else
        {
            return -1;
        }
    }
    catch (const invalid_argument &)
    {
        return -1; // 无法转换成数字
    }
    catch (const out_of_range &)
    {
        return -1; // 数字超出范围
    }
}

// 根据send和recv函数返回值判断客户端是否正常 来对socket、redis描述符、用户在线状态进行更改
// 函数部分：
void errorprocess(int fd)
{
}