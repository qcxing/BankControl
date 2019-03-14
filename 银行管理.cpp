#include<iostream>

#include<cstdio>

#include<cstdlib>
#include<atltime.h>

using namespace std;

#include<string>

#include<fstream>

#include<iomanip>
static double dayInterestRate=0.0001;

	static double taxRate=0.001;
	string managercode;
	static void setDailyInterestRate(double a)

	{
		dayInterestRate = a;

		cout << "成功设置日利率!" << endl;

		cout << "利率为：" << dayInterestRate << "%" << endl;
	}

	static void setTaxRate(double a)

	{
		taxRate = a;

		cout << "成功设置税率!" << endl;

		cout << "利率为：" << taxRate << "%" << endl;
	} 

	static void setmanagercode(string a)

	{
		managercode = a;

		cout << "密码设置成功！" << endl;
	}

class information //定义基类information,用来储存用户信息

{

public:

	

	string userNum;

	string userName;

	string userID;

	string password;

	string status;

	double money;

	int day, month, year;

	int countday;

public:

	

	void change_money_li(int cday)

	{
		money = money + money*(dayInterestRate / (double)100)*(double)countday*(1 - (taxRate / (double)100));
	}

	void add_money(double mon)

	{
		money += mon;
	}

	information() {}
	information(string a, string b, string c, string d, string e, int g, int y, int m, int da) //声明基类information中的7个对象

	{
		userNum = a;

		userName = b;

		userID = c;

		password = d;

		status = e;

		money = g;

		day = da;

		month = m;

		year = y;

	}



	void set_password(string a)

	{
		password = a;
	}

	string get_userNum() //获取银行卡号

	{

		return userNum;

	}

	string get_password() //获取密码

	{

		return password;

	}

	string get_status() //获取用户状态

	{

		return status;

	}

	double get_money() //获取用户金额

	{

		return money;

	}

	void display() //输出用户基本信息

	{
		cout << "以下是用户信息：" << endl;

		cout << "********************\n";

		cout << "银行卡号：" << userNum << endl;

		cout << "用户姓名：" << userName << endl;

		cout << "用户身份证号：" << userID << endl;

		cout << "用户密码：" << password << endl;

		cout << "开户时间：" << year << "年" << month << "月" << day << "日" << endl;
		cout << "用户密码：" << password << endl;

		cout << "用户状态：" << status << endl;

		cout << "用户金额：" << setiosflags(ios::fixed) << setprecision(3) << money << endl;

		cout << "********************\n";

		cout << endl;

	}



	void Wait()

	{

		long j = 0;

		for (double i = 1000000; i > 0;)

		{

			i = i - 0.002;

			j++;

			j--;

		}

	}

	void writeDailyInterRate()

	{
		ofstream stuf1("E:\\高层管理数据日利率.txt", ios::out);

		stuf1 << setiosflags(ios::fixed) << setprecision(3) << dayInterestRate << " "; stuf1.close();

		cout << "保存成功！" << endl;

		cout << endl;

	}

	
	void writesui()

	{
		ofstream stuf2("E:\\高层管理数据税率.txt", ios::out);

		stuf2 << setiosflags(ios::fixed) << setprecision(3) << taxRate << " "; stuf2.close();

		cout << "保存成功！" << endl;

		cout << endl;

	}
};

class manager :public information//派生类manager对用户信息进行管理

{

private:

	information B[1000];

	int sum;


public:
	manager()

	{
		sum = 0;
	}

	 

	void showuserAccountNumber()

	{

		cout << "您的银行卡账号为：" << setw(6) << setfill('#') << sum << endl;

	}

	void OpenAccount(information a) //开户

	{

		B[sum] = a;

		sum++;

		cout << "开户成功!" << endl;

		cout << endl;

		write();

	}

	void CloseAccount(information a) //销户

	{
		string code; char c;

		int flag = 0;

		int count = 0;

		if (sum == 0)

		{

			cout << "不存在该用户，销户失败！" << endl;

		}

		else

		{

			for (int i = 0; i < sum; i++)

			{

				if (B[i].get_userNum() == a.get_userNum())

				{

					cout << "找到该用户" << endl;

					cout << "请输入密码：" << endl;

					cin >> code;

					while (B[i].get_password() != code&&count <= 3)

					{
						cout << "密码错误,请重新输入: (您只有三次机会）";

						cin >> code;

						count++;
					}

					if (B[i].get_password() == code)

					{
						B[i].display();

						count++;

						cout << "确认-Y/取消-N: ";

						cin >> c;

						if (c == 'Y' || c == 'y')

						{
							for (int j = i; j < sum - 1; j++)

							{

								B[j] = B[j + 1];

							}

							flag = 1;

							sum--;

							cout << "销户成功！" << endl; break;

						}
					}

					if (count > 3) break;

				}

			}

			if (!flag)

			{

				cout << "该用户不存在!" << endl;

			}

		}
		write();


	}

	void HookAccount(information a) //用户挂失

	{
		char c;

		int flag = 0;

		for (int i = 0; i < sum; i++)

		{

			if (B[i].get_userNum() == a.userNum)

			{

				if (B[i].get_status() == "HOOK")

				{

					cout << "该用户已挂失！" << endl;

					cout << endl;

					break;

				}

				else

				{
					cout << endl;

					B[i].display();

					cout << "确认-Y/取消-N: ";

					cin >> c;

					if (c == 'Y' || c == 'y')

					{
						flag = 1;

						B[i].status = "HOOK";

						cout << "挂失成功！" << endl;

						cout << endl;
					}

				}

			}

		}

		if (flag == 0)

		{

			cout << "该用户不存在!" << endl; cout << endl;

		}

	}

	void UnhookAccount(information a)

	{
		char c; int i;

		int flag = 0;

		for (i = 0; i < sum; i++)

		{

			if (B[i].get_userNum() == a.userNum)

			{

				if (B[i].get_status() == "UNHOOK")

				{

					cout << "该用户无进行过挂失处理！" << endl; cout << endl;

					break;

				}

				else

				{

					B[i].display();

					cout << "确认-Y/取消-N: ";

					cin >> c;

					if (c == 'Y')

					{
						flag = 1;

						B[i].status = "UNHOOK";

						cout << "取消挂失成功！" << endl; cout << endl;

					}

				}

			}

		}

		if (flag == 0)

		{

			cout << "错误！该用户不存在!" << endl; cout << endl;

		}

	}

	void Saving( information & a, double mon) //存款

	{
		int i;

		for (i = 0; i < sum; i++)

		{

			if (B[i].get_userNum() == a.userNum)

			{
				if (B[i].get_status() == "HOOK")

				{
					cout << "对不起，用户已被冻结，无法修改！" << endl; cout << endl;
				}

				else

				{

					//计算与转入利息 

					{

						CTime begintime = CTime(year, month, day);

						CTime curtime = CTime::GetCurrentTime();

						CTimeSpan span;

						span = curtime - begintime;

						B[i].change_money_li(span.GetDays());

						B[i].year = curtime.GetYear();

						B[i].month = curtime.GetMonth();

						B[i].day = curtime.GetDay();

					}

					B[i].add_money(mon);

					cout << "成功存款：" << mon << endl;

					cout << endl;
				}

			}

		}

		if (i == sum + 1)

		{
			cout << "错误该用户不存在！" << endl; cout << endl;
		}

	}

	void Drawing(information a, double mon) //取款

	{
		int i; char c;

		for (i = 0; i <= sum; i++)

		{

			if (B[i].get_userNum() == a.userNum)

			{
				if (B[i].get_status() == "HOOK")

				{
					cout << "对不起，用户已被冻结，无法修改！" << endl; cout << endl;
				}

				else

				{

					if (mon > B[i].money)

					{
						cout << "您的余额不足！无法进行取款！" << endl; cout << endl;
					}

					else

					{
						//计算与转入利息 

						{

							CTime begintime = CTime(year, month, day);

							CTime curtime = CTime::GetCurrentTime();

							CTimeSpan span;

							span = curtime - begintime;

							B[i].change_money_li(span.GetDays());

							B[i].year = curtime.GetYear();

							B[i].month = curtime.GetMonth();

							B[i].day = curtime.GetDay();
						
						}

						B[i].add_money(-mon);

						cout << "成功取款：" << mon << endl;

						cout << "打印拼条？y/n" << endl;

						cin >> c;

						if (c == 'y' || c == 'Y')

						{
							cout << "凭条打印中，请稍后！" << endl;

							B[i].Wait();

							cout << "余额：" << setiosflags(ios::fixed) << setprecision(3) << B[i].get_money() << endl; cout << endl;

						}

					}

				}

			}

		}

		if (i == sum + 1)

		{
			cout << "错误该用户不存在！" << endl; cout << endl;
		}

	}

	void Transfering(information a) //转账

	{
		string usernum1;

		int j;

		int i;

		int mon;

		char c;

		for (i = 0; i <= sum; i++)

		{

			if (B[i].get_userNum() == a.userNum)

			{
				if (B[i].get_status() == "HOOK")

				{
					cout << "对不起，用户已被冻结，无法修改！" << endl; cout << endl;
				}

				else

				{


					//计算与转入利息 

					{


						CTime begintime = CTime(year, month, day);

						CTime curtime = CTime::GetCurrentTime();

						CTimeSpan span;

						span = curtime - begintime;

						B[i].change_money_li(span.GetDays());

						B[i].year = curtime.GetYear();

						B[i].month = curtime.GetMonth();

						B[i].day = curtime.GetDay();

					}
					cout << "请输入要转账的银行卡号：";

					cin >> usernum1;

					for (j = 0; j < sum; j++)

					{

						if (B[j].get_userNum() == usernum1)

						{
							cout << "请输入要转账的金额：" << endl;

							cin >> mon;

							if (mon > B[i].money)

							{
								cout << "您的余额不足！无法进行转账！" << endl; cout << endl;
							}

							else

							{


								B[i].add_money(-mon);

								B[j].add_money(mon);

								cout << "成功从用户：" << B[i].get_userNum() << "转账到用户：" << B[j].get_userNum() << endl;



								cout << "转账金额为：" << mon; cout << endl;
							}

						}

					}

				}

					

						

				

			}

		}
		
		if (j == sum + 1)

			cout << "该用户不存在！" << endl; cout << endl;
	}

	void Inquiring(information a) //查询

	{
		int i;

		for (i = 0; i <= sum; i++)

		{

			if (B[i].get_userNum() == a.userNum)

			{

				//计算与转入利息 

				{


					CTime begintime = CTime(year, month, day);

					CTime curtime = CTime::GetCurrentTime();

					CTimeSpan span;

					span = curtime - begintime;

					B[i].change_money_li(span.GetDays());

					B[i].year = curtime.GetYear();

					B[i].month = curtime.GetMonth();

					B[i].day = curtime.GetDay();

					

				}
				B[i].display();

			}

		}

		if (i == sum + 1)

			cout << "该用户不存在！" << endl;

	}

	void ModifyPassword(information a, string pass) //更改密码

	{

		for (int i = 0; i < sum; i++)

		{

			if (B[i].get_userNum() == a.userNum)

			{

				B[i].set_password(pass);

				cout << "成功修改密码！" << endl;

			}

		}

	}

	void read() //创建文件或从文件中读取信息

	{

		ifstream instuf1("E:\\bank.txt", ios::in);

		if (!instuf1 )  //

		{

			ofstream outstuff("E:\\bank.txt", ios::out);


			outstuff.close();

			ofstream p("E:\\高层管理数据管理密码.txt", ios::out);

			p.close();

			ofstream pp("E:\\高层管理数据用户数.txt", ios::out);

			pp.close();

			ofstream s("E:\\高层管理数据税率.txt", ios::out);

			s.close();


			cout << "创建文档成功!" << endl;

			cout << endl;

		}

		else

		{

			ifstream stuf("E:\\高层管理数据管理密码.txt", ios::in);

			stuf >> managercode;

			stuf.close();

			ifstream stuf1("E:\\高层管理数据日利率.txt", ios::in);

			stuf1 >>dayInterestRate;

			stuf1.close();

			ifstream stuf2("E:\\高层管理数据税率.txt", ios::in);

			stuf2 >> taxRate;

			stuf2.close();

			ifstream stuf3("E:\\高层管理数据用户数.txt", ios::in);

			stuf3 >> sum;

			stuf3.close();
			

			for (int i = 0; i<sum; i++)

			{
				instuf1 >> B[i].userNum >> B[i].userName >> B[i].userID >> B[i].password >> B[i].status >> B[i].money 
					>> B[i].year >> B[i].month >> B[i].day ;
			}

			cout << "读取数据成功!" << endl;

			cout << endl;

		}

		instuf1.close();

	}

	void writemanagercode()//密码

	{
		ofstream outstuf("E:\\高层管理数据管理密码.txt", ios::out);

		outstuf << managercode << " "; outstuf.close();

		cout << "保存成功！" << endl;

		cout << endl;

	}

	void write() //将信息存入文件"E:\\bank.txt"

	{
		ofstream pp("E:\\高层管理数据用户数.txt", ios::out);

		pp << sum;

		pp.close();

		ofstream f1("E:\\bank.txt", ios::out);

		if (!f1)

		{
			cout << "error" << endl;

			exit(1);

		}
		else 
		
		{



			for (int i = 0; i < sum; i++)

			{
				f1 << B[i].userNum << " " << B[i].userName << " " << B[i].userID << " " << B[i].password << " " << B[i].status << " " << setiosflags(ios::fixed) << setprecision(3) << B[i].money;

				f1 << " " << B[i].year << " " << B[i].month << " " << B[i].day  << endl;

			}
		}
		f1.close();

	}

	void tongji()

	{
		double countsum = 0;

		cout << "输出已建立的用户的余额统计:" << endl;

		cout << "银行卡号 " << " " << "余额" << endl;

		for (int i = 0; i< sum; i++)

		{
			cout << B[i].userNum << " " << B[i].money << endl;
		}

		cout << endl;

		for (int i = 0; i< sum; i++)

		{
			countsum += B[i].money;
		}

		cout << "用户总余额：" << countsum << endl;

		cout << endl;

		cout << endl;

	}

};


int main()

{
	int choice1; int choice2; int y1, m1, d1; int r1; double x, y; string a, a1;

	while (1)

	{


		cout << "************************************************\n";

		cout << "* 银行账户管理系统 *\n";

		cout << "* *\n";

		cout << "* 选择一个功能: *\n";

		cout << "* (1) 最高管理模式 *\n";

		cout << "* (2) 管理员模式 (Administrator Module) *\n";

		cout << "* (3) 用户模式 (User Module) *\n";

		cout << "* (4) 退出系统 *\n";

		cout << "************************************************\n";

		cout << "* Your Choice (1-4):";

		cin >> choice1;

		if (choice1 == 1) //最高管理模式，

		{
			char c1;

			manager worker; information user;

			int choice2;

			worker.read();

			while (1)

			{
				cout << "***********************************************\n";

				cout << "* 最高管理模式 *\n";

				cout << "* *\n";

				cout << "* 选择一个功能: *\n";

				cout << "* (1) 设置日息(%) *\n";

				cout << "* (2) 设置税率(%) *\n";

				cout << "* (3) 设置银行管理员权限密码 *\n";

				cout << "* (4) 返回主菜单 *\n";

				cout << "***********************************************\n";

				cout << "* Your Choice (1-4):";

				cin >> choice2;

				if (choice2 == 1)

				{
					cout << "请输入本银行日利率(%):" << endl;

					cin >> x;

					setDailyInterestRate(x);

					user.writeDailyInterRate();

				}

				else if (choice2 == 2)

				{
					cout << "请输入本银行税率(%):" << endl;

					cin >> y;

					cout << "确认-Y/取消-N" << endl;

					cin >> c1;

					if (c1 == 'Y' || c1 == 'y')

					{
						setTaxRate(y);

						user.writesui();

					}

				}

				else if (choice2 == 3)

				{
					cout << "请输入银行管理员密码：" << endl;

					cin >> a;

					cout << "请再次输入银行管理员密码：" << endl;

					cin >> a1;

					while (a != a1)

					{
						cout << "错误！请重新输入银行管理员密码：" << endl;

						cin >> a;

						cout << "请再次输入银行管理员密码：" << endl;

						cin >> a1;

					}

					setmanagercode(a);

					worker.writemanagercode();

				}

				else if (choice2 == 4)

				{

					for (int i = 0; i<3; i++)

					{

						cout << " " << endl;

					}

					for (int i = 0; i<48; i++)

					{

						cout << "*";

					}

					cout << endl;

					cout << "您已退出本模式系统，系统即将返回总菜单，请稍后!" << endl;


					break;

				}

			}

	 }

		else if (choice1 == 2) //管理员模式

		{

			manager worker; worker.read(); int choice2;

			string w;

			cout << "请输入管理员通行密码:" << endl;

			cin >> w;

			if (w == managercode)

			{
				cout << "密码输入正确！您可以进入银行账户管理系统(管理员)" << endl;

				cout << endl;

				cout << endl;

				while (1)

				{
					cout << "***********************************************\n";

					cout << "* 银行账户管理系统(管理员) *\n";

					cout << "* *\n";

					cout << "* 选择一个功能: *\n";

					cout << "* (1) 开户 *\n";

					cout << "* (2) 挂失 *\n";

					cout << "* (3) 解除挂失 *\n";

					cout << "* (4) 消户 *\n";

					cout << "* (5) 统计 *\n";

					cout << "* (6) 返回主菜单 *\n";

					cout << "***********************************************\n";

					cout << "* Your Choice (1-6):";

					cin >> choice2;

					cout << endl;

					if (choice2 == 1)

					{
						string a, b, c, d1, d2; int e, f, g, h; char c1;

						cout << "请输入用户卡号（6位）：" << endl;

						cin >> a;

						cout << "请输入用户姓名：" << endl;

						cin >> b;

						cout << "请输入用户身份证号：（18位）" << endl;

						cin >> c;

						cout << "请输入用户密码：（6位）" << endl;

						cin >> d1;

						cout << "请再次输入用户密码：" << endl;

						cin >> d2;

						while (d1 != d2)

						{
							cout << "错误！请重新输入用户密码：" << endl;

							cin >> d1;

							cout << "请再次输入用户密码：" << endl;

							cin >> d2;

						}

						cout << "请输入开户时间：";

						cin >> f;

						cin >> g;

						cin >> h;

						cout << "请输入储蓄金额：" << endl;

						cin >> e;

						cout << endl;

						information newuser(a, b, c, d1, "UNHOOK", e, f, g, h);

						newuser.display();

						cout << "确认-Y/取消-N" << endl;

						cin >> c1;

						if (c1 == 'Y' || c1 == 'y')

						{
							worker.OpenAccount(newuser); worker.write();
						}

					}

					else if (choice2 == 2)//选择挂失

					{
						string a;

						cout << "请输入要求挂失的卡号：" << endl;

						cin >> a;

						information newuser(a, " ", " ", " ", " ", 0, 0, 0, 0);

						worker.HookAccount(newuser); worker.write();

					}

					else if (choice2 == 3)//取消挂失

					{
						string a;

						cout << "请输入要求取消挂失的卡号：" << endl;

						cin >> a;

						information newuser(a, " ", " ", " ", " ", 0, 0, 0, 0);

						worker.UnhookAccount(newuser); worker.write();

					}

					else if (choice2 == 4)//销户

					{
						string a;

						cout << "请输入要求销户的卡号：" << endl;

						cin >> a;

						information newuser(a, " ", " ", " ", " ", 0, 0, 0, 0);

						worker.CloseAccount(newuser); worker.write();

					}

					else if (choice2 == 5) {
						worker.tongji();
					}

					else if (choice2 == 6)

					{

						

						cout << endl;

						cout << "您已退出本模式系统，系统即将返回总菜单，请稍后!" << endl;

						cout << endl;

						break;

					}

					

				}

			}

			else {
				cout << "密码错误！无法进入管理员模式!" << endl;

				cout << endl;
			}

		}

		else if (choice1 == 3) //用户模式

		{
			manager worker;

			int choice2;

			worker.read();

			while (1)

			{

				cout << "***********************************************\n";

				cout << "* 银行账户管理系统(用户) *\n";

				cout << "* *\n";

				cout << "* 功能选择: *\n";

				cout << "* (1) 存款 *\n";

				cout << "* (2) 取款 *\n";

				cout << "* (3) 查询 *\n";

				cout << "* (4) 转账 *\n";

				cout << "* (5) 更改密码 *\n";

				cout << "* (6) 取卡 *\n";

				cout << "***********************************************\n";

				cout << "* Your Choice (1-6):" << endl;

				cin >> choice2;

				if (choice2 == 1)

				{
					string a, b; char c; double mon;

					cout << "请输入银行卡账号：" << endl;

					cin >> a;

					cout << "输入密码：" << endl;

					cin >> b;

					information newuser(a, " ", " ", b, " ", 0, 0, 0, 0);

					cout << "确认-Y/取消-N" << endl;

					cin >> c;

					if (c == 'Y' || c == 'y')

					{
						cout << "请输入存入的金额：" << endl;

						cin >> mon;

						worker.Saving(newuser, mon); worker.write();

					}

					else

					{
						cout << "错误！" << endl;
					}

				}

				else if (choice2 == 2)

				{
					string a, b; char c; double mon;

					cout << "请输入银行卡账号：" << endl;

					cin >> a;

					information newuser(a, " ", " ", " ", " ", 0, 0, 0, 0);

					cout << "确认-Y/取消-N" << endl;

					cin >> c;

					if (c == 'Y' || c == 'y')

					{
						cout << "请输入要取出的金额：" << endl;

						cin >> mon;

						worker.Drawing(newuser, mon); worker.write();

					}

					else

					{
						cout << "错误！" << endl;
					}

				}

				else if (choice2 == 4)

				{
					string a, b; char c; double mon;

					cout << "请输入银行卡账号：" << endl;

					cin >> a;

					information newuser(a, " ", " ", " ", " ", 0, 0, 0, 0);

					cout << "确认-Y/取消-N" << endl;

					cin >> c;

					if (c == 'Y' || c == 'y')

					{

						worker.Transfering(newuser); worker.write();

					}

					else

					{
						cout << "错误！" << endl;
					}

				}

				else if (choice2 == 3)

				{
					string a, b; char c; double mon;

					cout << "请输入银行卡账号：" << endl;

					cin >> a;

					information newuser(a, " ", " ", " ", " ", 0, 0, 0, 0);

					cout << "确认-Y/取消-N" << endl;

					cin >> c;

					if (c == 'Y' || c == 'y')

					{

						worker.Inquiring(newuser); worker.write();

					}

					else

					{
						cout << "错误！" << endl;
					}

				}

				else if (choice2 == 5)

				{
					string a, f1, f2; char c;

					cout << "请输入银行卡账号：" << endl;

					cin >> a;


					information newuser(a, " ", " ", " ", " ", 0, 0, 0, 0);

					cout << "确认-Y/取消-N" << endl;

					cin >> c;

					if (c == 'Y' || c == 'y')

					{
						cout << "请输入新密码：" << endl;

						cin >> f1;

						cout << "请再次输入密码：" << endl;

						cin >> f2;

						while (f1 != f2)

						{
							cout << "错误！请重新输入密码：" << endl;

							cin >> f1;

							cout << "请再次输入密码：" << endl;

							cin >> f2;
						}

						worker.ModifyPassword(newuser, f1); worker.write();

					}

					else

					{
						cout << "错误！" << endl;
					}

				}

				else if (choice2 == 6)

				{

				

					cout << endl;

					cout << "您已退出本模式系统，系统即将返回总菜单，请稍后!" << endl;

				 cout << endl;

					break;
				}

			}

		}

		else if (choice1 == 4) 
		{
			
			
			
			
			break; }

	}

}