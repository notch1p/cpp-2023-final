// #include <bitset> STL is forbidden to use.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define getnum(x) scanf("%d", &(x))
typedef unsigned unsint;
using namespace std;

// bitset<10000> isDisabled;
bool isDisabled[10000];

// add bom to header to prevent wrong encoding  e.g. excel.
static inline void addBom(FILE* dataBase)
{
    const char bom_alt[] = "\xef\xbb\xbf";
    fprintf(dataBase, "%s", bom_alt);
}

static inline char getParams()
{
    char param[10000];
    printf("请选择一项操作： ");
    scanf(" %s", param);
    if (strlen(param) > 1) {
        printf("输入无效\n");
        return '0';
    }
    return param[0];
}

static inline void printPyramid()
{
    for (auto i = 0; i < 10; i++) {
        for (auto j = 0; j <= i; j++) {
            putchar('.');
        }
        putchar('\n');
    }
}

bool login()
{
    const char userName[] = "admin", passwd[] = "SCNU";
    char nameInput[20] = { 0 };
    char passwdInput[20] = { 0 };
    // lambda is not permitted in this scope.
    //  auto printAsterisks = [] { printf("******************************\n"); };
    printf("******************************\n");
    printf("*      图书销售管理系统      *\n");
    printf("******************************\n");
    int count = 3;
    while (count--) {
        printf("请输入用户名： ");
        scanf("%s", nameInput);
        printf("请输入密码： ");
        scanf("%s", passwdInput);
        if ((!strcmp(passwdInput, passwd)) && (!strcmp(userName, nameInput))) {
            printf("登录成功\n");
            return true;
        } else {
            printf("登录失败：您还有%d次机会\n", count);
        }
    }
    return false;
    exit(0);
}

// handles user database
struct userInfo {
    unsint offset = 8, num[10000] = { 1, 2, 3, 4, 5, 6, 7, 8 },
           score[10000] = { 100, 600, 500, 1000, 900, 100, 100, 100 };
    char name[10000][10] = { "张三", "李四", "王五", "陆六",
        "钱七", "大强", "小丽", "敏敏" };

    void print()
    {
        printf("图书销售管理系统 > 会员信息管理 > 显示会员信息\n");
        printf("**********************************\n");
        printf("%-s\t%-2s\t%12s\n", "会号", "姓名", "积分");
        for (int i = 0; i < 10000 && num[i]; i++) {
            printf("----------------------------------\n");
            printf("%-d\t%-2s\t%10d\n", num[i], name[i], score[i]);
        }
        printf("**********************************\n");
    }
    void append()
    {
        printf("图书销售管理系统 > 会员信息管理 > 新增会员信息\n");
        printf("输入新会员姓名&积分（以空格隔开）： \n");
        scanf("%s %d", name[offset], &score[offset]);
        num[offset] = offset + 1;
        offset++;
        printf("添加成功\n");
    }
    void edit()
    {
        int index, tempScore;
        char tempName[10] = { 0 };
        printf("图书销售管理系统 > 会员信息管理 > 修改会员信息\n");
        printf("输入需要更改的会员号&姓名&积分（以空格隔开）： \n");
        scanf("%d %s %d", &index, tempName, &tempScore);
        index--;
        if (index >= 0 && index < offset) {
            for (auto& i : name[index]) {
                i = 0;
            }
            int temp = 0;
            for (auto i : tempName) {
                name[index][temp++] = i;
            }
            score[index] = tempScore;
            printf("修改成功\n");
        } else
            printf(
                "!!Warning!! Out of range. Will cause segmentation fault.\nBack "
                "to main menu...\n");
    }
    void dump()
    {
        printf("图书销售管理系统 > 会员信息管理 > 导出数据库\n");
        char confirmation = '\0';
        char defaultPath[] = "./users.csv";
        char pathEnter[10000];
        fflush(stdin);
        printf("请输入保存路径（留空为默认./users.csv）： \n");
        fgets(pathEnter, 10000, stdin);
        printf("是否导出（将覆盖现有同路径文件）(Y)： ");
        scanf(" %c", &confirmation);
        if (confirmation == 'Y') {
            FILE* dataBase = fopen(pathEnter[0] == '\n' ? defaultPath : (pathEnter[strlen(pathEnter) - 1] = '\0', pathEnter), "w+");
            // add BoM to prevent certain client (e.g.) messing up w/ encoding.
            addBom(dataBase);
            // prototype below.
            //  const char bom_alt[] = "\xef\xbb\xbf";
            //  fprintf(dataBase, "%s", bom_alt);
            fprintf(dataBase, "%s,%s,%s\n", "编号", "姓名", "积分");
            for (auto i = 0; i < offset && num[i]; i++) {
#ifdef _WIN32 // use CRLF for Windows.
                fprintf(dataBase, "%d,%s,%d\n", num[i], name[i], score[i]);
                printf("%d,%s,%d\n", num[i], name[i], score[i]);
#else // use LF for other unix like systems.
                fprintf(dataBase, "%d,%s,%d\n", num[i], name[i], score[i]);
                printf("%d,%s,%d\n", num[i], name[i], score[i]);
#endif
            }
            fclose(dataBase);
            printPyramid();
            printf("*导出成功*\n");
        } else
            printf("操作取消，回到上级菜单....");
    }
    void import()
    {
        printf("图书销售管理系统 > 会员信息管理 > 导入数据库\n");
        printf("请输入欲导入的文件路径（将覆盖现有数据库）： \n");
        char pathEnter[10000];
        FILE* database;
        fflush(stdin);
        fgets(pathEnter, 10000, stdin);
        pathEnter[strlen(pathEnter) - 1] = '\0';
        if ((database = fopen(pathEnter, "r")) == NULL) {
            printf("文件不存在，回退到上一级菜单...\n");
        } else {
            char buf[10000];
            int iter = 0;
            fgets(buf, 10000, database);
            while (fgets(buf, 10000, database)) {
                sscanf(buf, "%d,%[^,\r\n],%d", &num[iter], name[iter], &score[iter]);
                printf("%d\t%-30s\t%5d\n", num[iter], name[iter], score[iter]);
                iter++;
            }
            offset = iter;
            fclose(database);
        }
        if (ferror(database)) {
            printf("Error writing to files. Redirecting...\n");
        } else
            printf("导入成功\n");
    }
} users;

// handles book database
struct bookInfo {
    unsint num[10000] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, offset = 9, decayedCount = 0,
           price[10000] = { 88, 55, 60, 45, 66, 68, 78, 29, 38 };
    char name[10000][100] = {
        "CSharp宝典", "Java编程基础", "J2SE桌面应用程序开发",
        "数据库设计和应用", "水浒传", "红楼梦",
        "三国演义", "地心游记", "心灵鸡汤"
    };
    void print()
    {
        printf("图书销售管理系统 > 书籍管理 > 查看上架书籍\n");
        // auto printAsterisks = [] { printf("********************************************************************************************************\n"); };
        // auto printHorizontalLines = [] { printf("--------------------------------------------------------------------------------------------------------\n"); };
        printf("********************************************************************************************************\n");
        printf("%-10s\t%-88s\t%8s\n", "图书号", "图书名", "图书价格");
        for (int i = 0; i < offset && num[i]; i++) {
            if (!isDisabled[i]) {
                char bookTitle[104];
                int j = 0;
                for (j = 2; j < strlen(name[i]) + 2; j++) {
                    bookTitle[j] = name[i][j - 2];
                }
                bookTitle[0] = '<';
                bookTitle[1] = '<';
                bookTitle[j] = '>';
                bookTitle[j + 1] = '>';
                bookTitle[j + 2] = '\0';
                printf("--------------------------------------------------------------------------------------------------------\n");
                printf("%-d\t%-88s\t%8u\n", num[i], bookTitle, price[i]);
            }
        }
        printf("********************************************************************************************************\n");
    }

    void printAll()
    {
        // auto printHorizontalLines = []{printf("----------------------------------------------------------------------------------------------------------------\n");};
        // auto printAsterisks = []{ printf("****************************************************************************************************************\n"); };
        printf("图书销售管理系统 > 书籍管理 > 查看数据库\n");
        printf("****************************************************************************************************************\n");
        printf("%-10s\t%-80s\t%8s\t%10s\n", "图书号", "图书名", "图书价格", "是否下架");
        for (int i = 0; i < offset && num[i]; i++) {
            bool disabled = isDisabled[i];
            printf("----------------------------------------------------------------------------------------------------------------\n");
            printf("%-d\t%-80s\t%8u\t%8s\n", num[i], name[i], price[i], isDisabled[i] ? "True" : "False");
        }
        printf("****************************************************************************************************************\n");
    }

    void append()
    {
        printf("图书销售管理系统 > 书籍管理 > 书籍添加\n");
        printf("请输入图书名&价格（空格分隔，书名中的空格用'-'代替）： \n");
        scanf("%s %u", name[offset], &price[offset]);
        num[offset] = offset + 1 - decayedCount;
        printf("添加成功\n");
        offset++;
    }
    void remove()
    {
        printf("图书销售管理系统 > 书籍管理 > 书籍下架\n");
        printf("请输入要删除的图书书名： \n");
        char temp[100], confirmation = '\0';
        scanf("%s", temp);
        bool isFounded = false;
        int i = 0;
        for (; i < offset; i++) {
            if (!isDisabled[i] && !strcmp(temp, name[i])) {
                isFounded = true;
                break;
            }
        }
        if (!isFounded)
            printf("书本不存在或已经删除\n");
        else {
            printf("找到该图书，编号为%d,是否删除(Enter 'Y' to confirm)： ", num[i]);
            scanf(" %c", &confirmation);
        }
        if (confirmation == 'Y') {
            decayedCount++;
            isDisabled[i] = isDisabled[i] | 1;
            printf("删除成功\n");
        } else
            printf("操作取消\n");
        // moving rest
        for (int j = i + 1; j < offset; j++) {
            num[j]--;
        }
    }
    void shrink()
    {
        int countPurged = 0;
        for (unsint i = 0; i < offset; i++) {
            if (isDisabled[i]) {
                countPurged++;
                for (unsint j = i + 1; j <= offset; j++) {
                    num[j - 1] = num[j];
                    for (unsint l = 0; l < sizeof(name[j - 1]); l++) {
                        name[j - 1][l] = '\0';
                    }
                    unsint index = 0;
                    for (auto chr : name[j])
                        name[j - 1][index++] = chr;
                    price[j - 1] = price[j];
                }
                isDisabled[i] = isDisabled[i] & 0;
            }
        }
        printf("Successfully purged %d slots\n", countPurged);
    }
    void dump()
    {
        printf("图书销售管理系统 > 书籍信息管理 > 导出数据库\n");
        char confirmation = '\0';
        char defaultPath[] = "./books.csv";
        char pathEnter[10000];
        fflush(stdin);
        printf("请输入保存路径（留空为默认./books.csv）： \n");
        fgets(pathEnter, 10000, stdin);
        printf("是否导出（将覆盖现有同路径文件）(Y)： ");
        scanf(" %c", &confirmation);
        if (confirmation == 'Y') {
            FILE* dataBase = fopen(pathEnter[0] == '\n' ? defaultPath : (pathEnter[strlen(pathEnter) - 1] = '\0', pathEnter), "w+");
            // add BoM to prevent certain client (e.g.) messing up w/ encoding.
            addBom(dataBase);
            // prototype below.
            //  const char bom_alt[] = "\xef\xbb\xbf";
            //  fprintf(dataBase, "%s", bom_alt);
            fprintf(dataBase, "%s,%s,%s,%s\n", "编号", "书名", "售价", "下架");
            for (auto i = 0; i < offset && num[i]; i++) {
#ifdef _win32 // use CRLF for Windows.
                fprintf(dataBase, "%d,%s,%d,%s\n", num[i], name[i], price[i], isDisabled[i] ? "True" : "False");
                printf("%d,%s,%d,%s\n", num[i], name[i], price[i], isDisabled[i] ? "True" : "False");
#else // use LF for other unix-like systems.
                fprintf(dataBase, "%d,%s,%d,%s\n", num[i], name[i], price[i], isDisabled[i] ? "True" : "False");
                printf("%d,%s,%d,%s\n", num[i], name[i], price[i], isDisabled[i] ? "True" : "False");
#endif
            }
            fclose(dataBase);
            printPyramid();
            printf("*导出成功*\n");
        } else
            printf("操作取消，回到上级菜单....");
    }
    void import()
    {
        printf("图书销售管理系统 > 书籍信息管理 > 导入数据库\n");
        printf("请输入欲导入的文件路径（将覆盖现有数据库）： \n");
        char pathEnter[10000];
        FILE* database;
        fflush(stdin);
        fgets(pathEnter, 10000, stdin);
        pathEnter[strlen(pathEnter) - 1] = '\0';
        if ((database = fopen(pathEnter, "r")) == NULL) {
            printf("文件不存在，回退到上一级菜单...\n");
        } else {
            char buf[10000];
            char bl[10];
            int iter = 0;
            fgets(buf, 10000, database);
            while (fgets(buf, 10000, database)) {
                sscanf(buf, "%d,%[^,],%d,%[^\r\n]", &num[iter], name[iter], &price[iter], bl);
                printf("%d\t%s\t%5d\t%s\n", num[iter], name[iter], price[iter], bl);
                if (bl[0] == 'T')
                    isDisabled[iter] |= 1;
                else
                    isDisabled[iter] &= 0;
                iter++;
            }
            offset = iter;
            fclose(database);
        }

        printf("导入成功\n");
    }
} books;

void userManagement() // user management UI
{
    // auto printAsterisks = [] { printf("**************************\n"); };
    while (true) {
        printf("图书销售管理系统 > 会员管理\n");
        printf("**************************\n");
        printf("*  1.显示所有会员        *\n");
        printf("*  2.添加会员信息        *\n");
        printf("*  3.修改会员信息        *\n");
        printf("*  4.导出数据库          *\n");
        printf("*  5.导入数据库          *\n");
        printf("*  6.返回主菜单          *\n");
        printf("**************************\n");
        switch (getParams()) {
        case '1':
            users.print();
            break;
        case '2':
            users.append();
            break;
        case '3':
            users.edit();
            break;
        case '4':
            users.dump();
            break;
        case '5':
            users.import();
            break;
        case '6':
            return;
        }
    }
}

// book management UI
void bookManagement()
{
    // auto printAsterisks = [] { printf("****************\n"); };
    while (true) {
        printf("图书销售管理系统 > 书籍管理\n");
        printf("****************\n");
        printf("* 1.查看在售书 *\n");
        printf("* 2.查看数据库 *\n");
        printf("* 3.添加书籍   *\n");
        printf("* 4.下架书籍   *\n");
        printf("* 5.压缩数据库 *\n");
        printf("* 6.导出数据库 *\n");
        printf("* 7.导入数据库 *\n");
        printf("* 8.返回主菜单 *\n");
        printf("****************\n");
        switch (getParams()) {
        case '1':
            books.print();
            break;
        case '2':
            books.printAll();
            break;
        case '3':
            books.append();
            break;
        case '4':
            books.remove();
            break;
        case '5':
            books.shrink();
            break;
        case '6':
            books.dump();
            break;
        case '7':
            books.import();
            break;
        case '8':
            return;
        }
    }
}

// checkout UI
void checkout()
{
    while (true) {
        printf("图书销售管理系统 > 购物结算\n");
        books.print();
        printf("请输入您的会员号&购入书号&数量（空格分隔）： \n");
        int userNum, bookNum, quant;
        scanf("%d %d %d", &userNum, &bookNum, &quant);
        int totalPrice = quant * books.price[bookNum - 1];
        printf("您购入%d本《%s》,共计%d元\n", quant, books.name[bookNum - 1], totalPrice);
        if (totalPrice > users.score[userNum - 1]) {
            printf("您的余额不足，回退到主菜单...\n");
            return;
        } else {
            printf("确认支付(Enter 'Y' to confirm): ");
            char temp;
            scanf(" %c", &temp);
            if (temp == 'Y') {
                users.score[userNum - 1] -= totalPrice;
                printf("支付成功，您现在的余额为%d元\n", users.score[userNum - 1]);
            } else {
                printf("支付取消，回退到主菜单...\n");
                return;
            }
        }
        printf("是否继续购买?(Enter anything but 'N' or 'n' to confirm)： ");
        char param[10000];
        scanf(" %s", param);
        if (param[0] == 'N' || param[0] == 'n') {
            printf("回退到主菜单...\n");
            return;
        }
    }
}

// main UI
int mainInterface()
{
    int param;
    // auto printAsterisks = [] { printf("******************************\n"); };
    printf("******************************\n");
    printf("*      图书销售管理系统      *\n");
    printf("*         1.会员管理         *\n");
    printf("*         2.书籍管理         *\n");
    printf("*         3.购物结算         *\n");
    printf("*         4.注销             *\n");
    printf("*         5.退出程序         *\n");
    printf("******************************\n");
    return getParams();
}

int main()
{
    bool loginStatus = login();
    while (loginStatus) {
        switch (mainInterface()) {
        case '1':
            userManagement();
            break;
        case '2':
            bookManagement();
            break;
        case '3':
            checkout();
            break;
        case '4':
            loginStatus = false;
            printf("您已登出\n");
            loginStatus = login();
            break;
        case '5':
            exit(0);
        }
    }
}