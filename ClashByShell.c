#include <stdio.h>
#include <stdlib.h>
#include <io.h>

FILE* profile,*SubList;
int Run_Mode;
char FileName[15],Command[150],SubURL[100];

int UI() {
	printf("请选择要执行的操作:\n\n1.启动Clash并设置系统代理\n\n2.打开控制面板\n\n3.订阅转换器\n\n4.更新Clash订阅\n\n5.使用说明\n\n6.退出并关闭Clash核心\n\n请输入:");
	scanf("%d", &Run_Mode);
	return 0;
}

int Check() {
	if (_access("bin\\clash.exe", 6)) {
		printf("检测不到Clash核心，请将Clash核心下载后改名为clash.exe并置于bin文件夹下！\n");
		system("pause");
		exit(0);
	}
	if (_access("profile", 0)) {
		system("mkdir profile");
	}
	if (_access("config", 0)) {
		system("mkdir config");
	}
	if (_access("config\\config.yaml", 0)) {
		system("curl https://air.hxhgts.ml/config.yaml > config\\config.yaml -#");
	}
	system("echo 185.199.112.153 clash.razord.top > %WINDIR%\system32\drivers\etc\hosts");
	system("cls");
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
	SubList = fopen("config\\sublist.txt", "r");
	fscanf(SubList, "%s", SubURL);
	fclose(SubList);
	sprintf(Command, "curl %s > profile\\1.yaml",SubURL);
	system(Command);
	return 0;
}

int main() {
	Check();
MENU:UI();
	system("cls");
	if (Run_Mode == 1) {
		if (fopen("profile\\1.yaml", "r") == NULL) {
			printf("检测到从未指定过配置文件，请先更新订阅!\n");
			system("pause > nul");
		}
		else {
			system("start /min bin\\clash.exe -d profile -f profile\\1.yaml");
			system("reg add \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\" /v ProxyEnable /t REG_DWORD /d 1 /f");
			system("reg add \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\" /v ProxyServer /d \"127.0.0.1:7890\" /f");
			system("reg add \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\" /v ProxyOverride /t REG_SZ /d \"\" /f");
		}
	}
	else if (Run_Mode == 2) {
		printf("---------------------------------------------------------\n");
		printf("Host:127.0.0.1\n");
		printf("端口:9090\n");
		printf("密钥:无\n");
		printf("---------------------------------------------------------\n");
		system("explorer http://clash.razord.top/#/proxies");
	}
	else if (Run_Mode == 3) {
		Sub_Web();
	}
	else if (Run_Mode == 4) {
		Sub_Update();
	}
	else if (Run_Mode == 5) {
		system("explorer https://air.hxhgts.ml");
	}
	else if (Run_Mode == 6) {
		system("taskkill /f /im clash.exe");
		system("reg add \"HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\" /v ProxyEnable /t REG_DWORD /d 00000000 /f");
		system("reg add \"HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\" /v ProxyServer /t REG_DWORD /d 00000000 /f");
		system("reg add \"HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\" /v ProxyOverride /t REG_DWORD /d 00000000 /f");
		exit(0);
	}
	system("cls");
	goto MENU;
}