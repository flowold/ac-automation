#include <iostream>
#include<fstream>
#include <time.h>
#include "Node.h"
#include "Automation.h"

using namespace std;

void string_replace(string &strBig, const string &strsrc, const string &strdst);

int main() {

    cout << "\n\n" << endl;

    clock_t starts, ends;
    Automation *automation = new Automation;


    ifstream fin("../example/words.txt");
    string word;

    starts = clock();
    int counts = 0;
    if (fin) {
        while (getline (fin, word)) {
            string_replace(word, "\n", "");
            string_replace(word, "\r", "");
            automation->add(word);
            ++counts;
        }
    } else {
        cout <<"字典读取失败！" << endl;
    }
    automation->build();
    ends = clock();
    cout << "创建字典成功！ 字典条目数: " << counts << " 耗时:" << ends - starts << "ms\n" << endl;


    // 打印字典
    // automation->print();

    ifstream buf("../example/post.txt");
    string str((istreambuf_iterator<char>(buf)), istreambuf_iterator<char>());

    //string_replace(str, "\r\n", "  ");

    starts = clock();
    bool isMatched = automation->match(str);
    ends   = clock();
    cout << "字典命中结果: " << (isMatched ? "成功 !" : "失败 !") << " 耗时:" << (ends - starts) << "ms\n" << endl;


    starts = clock();
    cout << "命中的关键词:" << endl;
    cout << "--------------------------------" << endl;
    map<string, Node*> nodes;
    automation->search(str, nodes);
    int n = 0;
    for (map<string, Node*>::iterator item = nodes.begin(); item != nodes.end(); ++ item) {
        cout << "匹配  : " << item->second->word << endl;
        cout << "词频  : " << item->second->repeats << endl;
        cout << "首位  : " << item->second->index << endl;
        ++n;
        cout << "--------------------------------" << endl;
    }
    ends   = clock();
    cout << "\n文章长度: " << str.size() << "命中 " << n << "个关键词" << " 耗时:" << (ends - starts) << "ms\n" << endl;


    delete automation;

    return 0;
}

void string_replace(string &strBig, const string &strsrc, const string &strdst)
{
    string::size_type pos = 0;
    string::size_type srclen = strsrc.size();
    string::size_type dstlen = strdst.size();

    while( (pos=strBig.find(strsrc, pos)) != string::npos )
    {
        strBig.replace( pos, srclen, strdst );
        pos += dstlen;
    }
}
