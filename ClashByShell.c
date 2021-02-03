#include <stdio.h>
#include <stdlib.h>
#include <io.h>

FILE* profile,*SubList,*Log;
int Run_Mode,Sub_Use,Log_level;
char FileName[15],Command[160],SubURL[100];
char UserAgent[23]="ClashforWindows/0.14.3";

int UI() {
	if (!_access("log\\clash.health", 0)) {
		printf("--------------------------------------------\n");
		printf("检测到Clash核心在后台运行，请不要关闭本窗口!\n");
		printf("--------------------------------------------\n\n");
	}
	printf("请选择要执行的操作:\n\n1.启动Clash并设置系统代理\n\n2.打开控制面板\n\n3.订阅转换器\n\n4.更新Clash订阅\n\n5.解除UWP应用本地回环限制\n\n6.使用说明\n\n7.退出并关闭Clash核心\n\n请输入:");
	scanf("%d", &Run_Mode);
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
	if (_access("bin\\clash.exe", 6)) {
		printf("检测不到Clash核心或Clash核心被占用，按任意键退出！\n");
		system("pause > nul");
		exit(0);
	}
	return 0;
}

int Sub_Web() {
	system("explorer https://hxhgts.ml/ClashRuleTransfer/");
	return 0;
}

int Sub_Update() {
	if (fopen("config\\sublist.txt", "r") == NULL) {
		printf("请输入订阅地址:");
		scanf("%s", SubURL);
		SubList = fopen("config\\sublist.txt", "w");
		fprintf(SubList, "%s", SubURL);
		fclose(SubList);
	}
	else {
		printf("检测到保存的订阅地址,是否覆盖?\n\n1.是\n\n0.否\n\n请输入:");
		scanf("%d", &Sub_Use);
		system("cls");
		if (Sub_Use == 1) {
			printf("请输入订阅地址:");
			scanf("%s", SubURL);
			SubList = fopen("config\\sublist.txt", "w");
			fprintf(SubList, "%s", SubURL);
			fclose(SubList);
		}
	}
	system("cls");
	printf("是否保存运行日志?\n\n1.是\n\n0.否\n\n请输入:");
	scanf("%d", &Log_level);
	SubList = fopen("config\\sublist.txt", "r");
	fscanf(SubList, "%s", SubURL);
	fclose(SubList);
	Log = fopen("config\\log.conf", "w");
	fprintf(Log, "%d", Log_level);
	fclose(Log);
	system("cls");
	sprintf(Command, "curl -A \"%s\" \"%s\" > profile\\1.yaml",UserAgent,SubURL);
	system(Command);
	return 0;
}

int main() {
	Check();
MENU:UI();
	system("cls");
	if (Run_Mode == 1) {
		if (_access("profile\\1.yaml", 0)) {
			printf("检测到从未指定过配置文件，请先更新订阅!\n");
			system("pause");
			system("cls");
			Sub_Update();
		}
		else {
			system("taskkill /f /im clash.exe");
			Log = fopen("config\\log.conf", "r");
			fscanf(Log, "%d", &Log_level);
			fclose(Log);
			if (Log_level == 1) {
				system("start /b bin\\clash.exe -d profile -f profile\\1.yaml >> log\\log.txt");
			}
			else {
				system("start /b bin\\clash.exe -d profile -f profile\\1.yaml > nul");
			}
			system("echo 1 > log\\clash.health");
			system("reg add \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\" /v ProxyEnable /t REG_DWORD /d 1 /f");
			system("reg add \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\" /v ProxyServer /d \"http://127.0.0.1:7890,socks://127.0.0.1:7891\" /f");
			system("reg add \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\" /v ProxyOverride /t REG_SZ /d \"localhost;127.*;10.*;172.16.*;172.17.*;172.18.*;172.19.*;172.20.*;172.21.*;172.22.*;172.23.*;172.24.*;172.25.*;172.26.*;172.27.*;172.28.*;172.29.*;172.30.*;172.31.*;192.168.*;<local>\" /f");
			system("cls");
			printf("Clash已启动!按任意键回到主页(不会影响代理状态)\n");
			system("TIMEOUT 5");
		}
	}
	else if (Run_Mode == 2) {
		system("explorer http://clash.hxhgts.ml/#/proxies");
	}
	else if (Run_Mode == 3) {
		Sub_Web();
	}
	else if (Run_Mode == 4) {
		Sub_Update();
	}
	else if (Run_Mode == 5) {
		system("FOR /F \"tokens=11 delims=\\\" %p IN ('REG QUERY \"HKCU\\Software\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\CurrentVersion\\AppContainer\\Mappings\"') DO CheckNetIsolation.exe LoopbackExempt -a -p=%p");
	}
	else if (Run_Mode == 6) {
		printf("首次使用请先更新订阅,调整节点请使用控制台!\n");
		system("pause");
	}
	else if (Run_Mode == 7) {
		system("taskkill /f /im clash.exe");
		system("del log\\clash.health");
		system("reg add \"HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\" /v ProxyEnable /t REG_DWORD /d 00000000 /f");
		system("reg add \"HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\" /v ProxyServer /t REG_DWORD /d 00000000 /f");
		system("reg add \"HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\" /v ProxyOverride /t REG_DWORD /d 00000000 /f");
		exit(0);
	}
	system("cls");
	goto MENU;
}