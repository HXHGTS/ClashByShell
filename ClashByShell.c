#include <stdio.h>
#include <stdlib.h>
#include <io.h>

FILE* profile,*SubList;
int Main_Run_Mode,Sub_Run_Mode,Sub_Use,Sub_Num;
char FileName[20],Command[160],SubURL[100],FileAddr[18];
char UserAgent[19]="ClashByShell/0.4.0";

int UI() {
	if (!_access("working\\using.yaml", 0)) {
		printf("--------------------------------------------\n");
		printf("检测到Clash核心在后台运行，请不要关闭本窗口!\n");
		printf("代理地址:    127.0.0.1\n");
		printf("HTTP端口:    7890\n");
		printf("socks5端口:  7891\n");
		printf("--------------------------------------------\n\n");
		printf("请选择要执行的操作:\n\n1.更换配置文件&重启Clash\n\n2.打开控制面板\n\n3.更新Clash订阅\n\n4.解除UWP应用本地回环限制\n\n5.使用说明\n\n0.退出并关闭Clash核心\n\n请输入:");
	}
	else {
		printf("请选择要执行的操作:\n\n1.启动Clash并设置系统代理\n\n2.打开控制面板\n\n3.更新Clash订阅\n\n4.解除UWP应用本地回环限制\n\n5.使用说明\n\n0.退出并关闭Clash核心\n\n请输入:");
	}
	
	scanf("%d", &Main_Run_Mode);
	return 0;
}

int Check() {
	system("color 0B");
	if (_access("profile", 0)) {
		system("mkdir profile");
	}
	if (_access("config", 0)) {
		system("mkdir config");
	}
	if (_access("log", 0)) {
		system("mkdir log");
	}
	if (_access("bin", 0)) {
		system("mkdir bin");
	}
	if (_access("working", 0)) {
		system("mkdir working");
	}
	printf("正在检测Clash核心状态. . .\n");
	if (_access("bin\\clash.exe", 6)) {
		printf("----------------------------------------------------------------\n");
		printf("检测不到Clash核心，请将clash核心命名为clash.exe并放到bin文件夹中\n");
		printf("Clash核心可能被占用，请关闭其它clash软件，按任意键退出！\n");
		printf("----------------------------------------------------------------\n\n");
		system("pause > nul");
		exit(0);
	}
	else {
		printf("已经检测到Clash核心!\n");
		printf("正在检测国家级ip数据库. . .\n");
		if (_access("working\\Country.mmdb", 0)) {
			printf("正在下载国家级ip数据库. . .\n");
			system("echo port: 7890> working\\config.yaml");
			system("bin\\clash -d working -t working\\config.yaml");
		}
		printf("正在启动nginx. . .\n");
		system("start /b nginx\\nginx.exe -p nginx");
		system("cls");
	}
	return 0;
}

int Sub_Update() {
	int i;
	if (fopen("config\\sublist.txt", "r") == NULL) {
	printf("订阅保存的文件名:");
		scanf("%s", FileName);
		printf("请在弹出页输入订阅地址. . .\n");
		system("echo 请删掉这段文字并将订阅链接粘贴至此 > config\\1.yaml");
		system("notepad config\\1.yaml");
		SubList = fopen("config\\sublist.txt", "w");
		fprintf(SubList, "1.%s\n",FileName);
		fclose(SubList);
		system("cls");
		profile = fopen("config\\1.yaml", "r");
		fscanf(profile, "%s", SubURL);
		fclose(profile);
		printf("正在更新订阅. . .\n");
		sprintf(Command, "bin\\curl.exe -A \"%s\" \"%s\" > profile\\1.yaml", UserAgent, SubURL);
		system(Command);
	}
	else {
	Sub_Menu:printf("检测到保存的订阅地址,列出所有订阅:\n");
		printf("----------------------------------\n");
		system("type config\\sublist.txt");
		printf("----------------------------------\n");
		printf("需要添加并更新新订阅请输入0\n");
		printf("请选择需要操作的订阅，输入序号即可:");
		scanf("%d", &Sub_Use);
		system("cls");
		if (Sub_Use != 0) {
			printf("请选择需要的操作:\n\n1.修改订阅地址并更新订阅\n\n2.重命名\n\n3.删除此订阅\n\n4.退出\n\n请输入:");
			scanf("%d", &Sub_Run_Mode);
			system("cls");
			if (Sub_Run_Mode == 1) {
				printf("请在弹出页输入订阅地址. . .\n");
				sprintf(Command, "notepad config\\%d.yaml", Sub_Use);
				system(Command);
				system("cls");
				sprintf(FileAddr, "config\\%d.yaml", Sub_Use);
				profile = fopen(FileAddr, "r");
				fscanf(profile, "%s", SubURL);
				fclose(profile);
				printf("正在更新订阅. . .\n");
				sprintf(Command, "bin\\curl.exe -A \"%s\" \"%s\" > profile\\%d.yaml", UserAgent, SubURL, Sub_Use);
				system(Command);
			}
			else if (Sub_Run_Mode == 2) {
				printf("订阅保存的文件名:");
				scanf("%s", FileName);
				sprintf(Command, "type config\\sublist.txt | find /v \"%d.\" > config\\sublist.txt_temp", Sub_Use);
				system(Command);
				sprintf(Command, "echo %d.%s >> config\\sublist.txt_temp",Sub_Use,FileName);
				system(Command);
				sprintf(Command, "copy /y config\\sublist.txt_temp config\\sublist.txt");
				system(Command);
				sprintf(Command, "del /F /S /Q config\\sublist.txt_temp");
				system(Command);
				system("cls");
				goto Sub_Menu;
			}
			else if (Sub_Run_Mode == 3) {
				sprintf(Command,"del /F /S /Q profile\\%d.yaml",Sub_Use);
				system(Command);
				sprintf(Command, "del /F /S /Q config\\%d.yaml", Sub_Use);
				system(Command);
				sprintf(Command, "type config\\sublist.txt | find /v \"%d.\" > config\\sublist.txt_temp", Sub_Use);
				system(Command);
				sprintf(Command, "copy /y config\\sublist.txt_temp config\\sublist.txt");
				system(Command);
				sprintf(Command, "del /F /S /Q config\\sublist.txt_temp");
				system(Command);
				system("cls");
				goto Sub_Menu;
			}
			else {
				exit(0);
			}
		}
		else {
			for (i = 1; i <= 200; i++) {
				sprintf(FileAddr, "config\\%d.yaml", i);
				if (fopen(FileAddr, "r") == NULL) {
					Sub_Num = i;
					break;
				}
			}
			printf("订阅保存的文件名:");
			scanf("%s", FileName);
			printf("请在弹出页输入订阅地址. . .\n");
			sprintf(Command, "echo 请删掉这段文字并将订阅链接粘贴至此 > config\\%d.yaml", Sub_Num);
			system(Command);
			sprintf(Command, "notepad config\\%d.yaml", Sub_Num);
			system(Command);
			SubList = fopen("config\\sublist.txt", "a");
			fprintf(SubList, "%d.%s\n",Sub_Num, FileName);
			fclose(SubList);
			system("cls");
			sprintf(FileAddr, "config\\%d.yaml", Sub_Num);
			profile = fopen(FileAddr, "r");
			fscanf(profile, "%s", SubURL);
			fclose(profile);
			printf("正在更新订阅. . .\n");
			sprintf(Command, "bin\\curl.exe -A \"%s\" \"%s\" > profile\\%d.yaml", UserAgent, SubURL,Sub_Num);
			system(Command);
		}
	}
	system("cls");
	
	return 0;
}

int main() {
	Check();
Main_Menu:UI();
	system("cls");
	if (Main_Run_Mode == 1) {
		if (_access("profile\\1.yaml", 0)) {
			printf("检测到从未指定过配置文件，请先更新订阅!\n");
			system("pause");
			system("cls");
			Sub_Update();
		}
		else {
			printf("检测到保存的订阅地址,列出所有订阅:\n");
			printf("----------------------------------\n");
			system("type config\\sublist.txt");
			printf("----------------------------------\n");
			printf("请选择使用的订阅，输入序号即可:");
			scanf("%d", &Sub_Use);
			system("cls");
			system("taskkill /f /im clash.exe");
			sprintf(Command, "copy /y profile\\%d.yaml working\\using.yaml", Sub_Use);
			system(Command);
			sprintf(Command, "start /b bin\\clash.exe -d working -f working\\using.yaml > log\\log.txt");
			system(Command);
			system("reg add \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\" /v ProxyEnable /t REG_DWORD /d 1 /f");
			system("reg add \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\" /v ProxyServer /d \"127.0.0.1:7890\" /f");
			system("reg add \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\" /v ProxyOverride /t REG_SZ /d \"localhost;127.*;10.*;172.16.*;172.17.*;172.18.*;172.19.*;172.20.*;172.21.*;172.22.*;172.23.*;172.24.*;172.25.*;172.26.*;172.27.*;172.28.*;172.29.*;172.30.*;172.31.*;192.168.*;<local>\" /f");
			system("cls");
			printf("Clash已启动!按任意键回到主页(不会影响代理状态)\n");
			printf("正在打开控制台. . .\n");
			system("explorer http://127.0.0.1:8080/#/proxies");
		}
	}
	else if (Main_Run_Mode == 2) {
		printf("正在打开控制台. . .\n");
		system("explorer http://127.0.0.1:8080/#/proxies");
	}
	else if (Main_Run_Mode == 3) {
		Sub_Update();
	}
	else if (Main_Run_Mode == 4) {
		system("bin\\EnableLoopback.exe");
	}
	else if (Main_Run_Mode == 5) {
		printf("正在打开帮助. . .\n");
		system("explorer https://hxhgts.ml/ClashByShell/");
	}
	else if (Main_Run_Mode == 0) {
		printf("正在退出. . .\n");
		system("taskkill /f /im clash.exe");
		system("taskkill /f /im nginx.exe");
		system("del /F /S /Q nginx\\logs\\*");
		system("del /F /S /Q working\\using.yaml");
		system("reg add \"HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\" /v ProxyEnable /t REG_DWORD /d 00000000 /f");
		system("reg add \"HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\" /v ProxyServer /t REG_DWORD /d 00000000 /f");
		system("reg add \"HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\" /v ProxyOverride /t REG_DWORD /d 00000000 /f");
		exit(0);
	}
	system("cls");
	goto Main_Menu;
}